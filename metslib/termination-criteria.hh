#ifndef TERMINATION_CRITERIA_HH_
#define TERMINATION_CRITERIA_HH_

namespace mets {
  /// @defgroup common Common pieces
  /// @{

  /// @brief Function object expressing a
  /// termination criteria
  ///
  /// The tabu-search loop ends when the termination
  /// criteria is met.
  template<typename search_type>
  class termination_criteria_chain
  {
  public:
    /// @brief Constructor.
    /// 
    /// @param next Optional next criterium in the chain.
    explicit
    termination_criteria_chain(termination_criteria_chain<search_type>* 
			       next = 0)
      : next_m(next) 
    { }
    /// purposely not implemented (see Effective C++)
    termination_criteria_chain(const termination_criteria_chain<search_type>&
			       other);
    termination_criteria_chain<search_type>& 
    operator=(const termination_criteria_chain<search_type>& other);

    /// @brief Virtual destructor.
    virtual 
    ~termination_criteria_chain() 
    { }

    /// @brief The function that decides if we shoud terminate the
    /// search process
    ///
    /// @param fs The current working solution.
    /// @param as The search instance.
    /// @return True if we shoud terminate
    virtual bool 
    operator()(feasible_solution& fs, search_type& ts);

    /// @brief Alternate function that decides if we shoud terminate the
    /// search process
    ///
    /// @param fs The current working solution.
    /// @return True if we shoud terminate
    virtual bool 
    operator()(feasible_solution& fs);

    virtual void reset() = 0;

  protected:
    termination_criteria_chain<search_type>* next_m;
  };

  /// @brief Termination criteria based on the number of iterations.
  ///
  /// This termination criteria terminates the tabu-search
  /// after a fixed number of itarations.
  template<typename search_type>
  class iteration_termination_criteria 
    : public termination_criteria_chain<search_type>
  {
  public:
    /// @brief Ctor. Max is the number of iterations to do.
    iteration_termination_criteria(int max) 
      : termination_criteria_chain<search_type>(), 
	max_m(max), 
	iterations_m(max) {}
    explicit
    iteration_termination_criteria
    (termination_criteria_chain<search_type>* next, int max) 
      : termination_criteria_chain<search_type>(next), 
	max_m(max), 
	iterations_m(max) {}
    bool 
    operator()(feasible_solution& fs, search_type& ts)
    { 
      if (iterations_m <= 0) 
	return true; 
      
      --iterations_m;
      return termination_criteria_chain<search_type>::operator()(fs, ts); 
    }

    bool 
    operator()(feasible_solution& fs)
    { 
      if (iterations_m <= 0) 
	  return true; 

      --iterations_m;
      return termination_criteria_chain<search_type>::operator()(fs); 
    }
    void reset() { iterations_m = max_m; }
  protected:
    int max_m;
    int iterations_m;
  };

  /// @brief Termination criteria based on the number 
  /// of iterations without an improvement.
  ///
  /// This termination criteria terminates the tabu-search
  /// after "max" number of itarations without a single
  /// global improvement.
  template<typename search_type>
  class noimprove_termination_criteria 
    : public termination_criteria_chain<search_type>
  {
  public:
    noimprove_termination_criteria(int max) 
      : termination_criteria_chain<search_type>(),
	best_cost_m(std::numeric_limits<gol_type>::max()), 
	max_noimprove_m(max), 
	iterations_left_m(max),
	total_iterations_m(0),
	resets_m(0),
	second_guess_m(0)
    {}
    noimprove_termination_criteria
    (termination_criteria_chain<search_type>* next,
     int max) 
      : termination_criteria_chain<search_type>(next),
	best_cost_m(std::numeric_limits<gol_type>::max()), 
	max_noimprove_m(max), 
	iterations_left_m(max),
	total_iterations_m(0),
	resets_m(0),
	second_guess_m(0)
    {}

    bool 
    operator()(feasible_solution& fs, search_type& ts);

    bool 
    operator()(feasible_solution& fs);
    void reset() 
    { iterations_left_m = max_noimprove_m; 
      second_guess_m = total_iterations_m = resets_m = 0; 
      best_cost_m = std::numeric_limits<gol_type>::max();
    }
    int second_guess() { return second_guess_m; }
    int iteration() { return total_iterations_m; }
    int resets() { return resets_m; }
  protected:
    gol_type best_cost_m;
    int max_noimprove_m;
    int iterations_left_m;
    int total_iterations_m;
    int resets_m;
    int second_guess_m;
  };

  /// @brief Termination criteria based on cost value
  ///
  /// This termination criteria terminates the tabu-search
  /// when a certain threshold is reached
  template<typename search_type>
  class threshold_termination_criteria 
    : public termination_criteria_chain<search_type>
  {
  public:
    threshold_termination_criteria(gol_type level) 
      : termination_criteria_chain<search_type>(),
	level_m(level) 
    { } 

    threshold_termination_criteria
    (termination_criteria_chain<search_type>* next,
     gol_type level) 
      : termination_criteria_chain<search_type>(next),
	level_m(level) 
    { } 

    bool 
    operator()(feasible_solution& fs, search_type& ts)
    { 
      if(ts.best_cost() <= level_m) 
	return true; 

      return termination_criteria_chain<search_type>::operator()(fs, ts); 
    }

    bool 
    operator()(feasible_solution& fs)
    { 
      if(fs.cost_function() <= level_m) 
	return true; 

      return termination_criteria_chain<search_type>::operator()(fs); 
    }

    void reset() 
    { /* stateless */ };

  protected:
    gol_type level_m;
  };

  /// @}
}

//________________________________________________________________________

template<typename search_type>
bool 
mets::termination_criteria_chain<search_type>::operator()
  (feasible_solution& fs, 
   search_type& ts)
{
  if(next_m)
    return next_m->operator()(fs, ts);
  else
    return false;
}

template<typename search_type>
bool 
mets::termination_criteria_chain<search_type>::operator()(feasible_solution& fs)
{
  if(next_m)
    return next_m->operator()(fs);
  else
    return false;
}

template<typename search_type>
bool 
mets::noimprove_termination_criteria<search_type>::operator()
  (feasible_solution& fs, 
   search_type& ts)
{
  if(ts.best_cost() < best_cost_m - epsilon)
    {
      best_cost_m = ts.best_cost();
      second_guess_m = std::max(second_guess_m, 
				(max_noimprove_m - iterations_left_m));
      iterations_left_m = max_noimprove_m;
      resets_m++;
    }

  total_iterations_m++;

  if(--iterations_left_m <= 0)
      return true;

  return termination_criteria_chain<search_type>::operator()(fs, ts);
}

template<typename search_type>
bool 
mets::noimprove_termination_criteria<search_type>::operator()
  (feasible_solution& fs)
{
  gol_type cost = fs.cost_function();
  if(cost < best_cost_m - epsilon)
    {
      best_cost_m = cost;
      second_guess_m = std::max(second_guess_m, 
				(max_noimprove_m - iterations_left_m));
      iterations_left_m = max_noimprove_m;
      resets_m++;
    }

  total_iterations_m++;

  if(--iterations_left_m <= 0)
      return true;

  return termination_criteria_chain<search_type>::operator()(fs);
}


#endif
