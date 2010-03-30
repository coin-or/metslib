#ifndef SIMULATED_ANNEALING_HH_
#define SIMULATED_ANNEALING_HH_

namespace mets {
  /// @brief Search by Simulated Annealing.
  template<typename move_manager_type>
  class simulated_annealing : public mets::abstract_search<move_manager_type>
  {
  public:
    typedef simulated_annealing<move_manager_type> search_type;
    /// @brief Creates a search by simulated annealing instance.
    ///
    /// @param working The working solution (this will be modified
    /// during search).
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found.
    ///
    /// @param moveman A problem specific implementation of the
    /// move_manager_type used to generate the neighborhood.
    ///
    /// @param tc The termination criteria used to terminate the
    /// search process, this is an extension to the standard Simulated
    /// Annealing: you can give a termination criteria that termiantes
    /// when temperature reaches 0.
    ///
    /// @param cs The annealing schedule that decorates this SA instance.
    ///
    /// @param starting_temp The starting SA temperature.
    simulated_annealing(feasible_solution& starting_point,
			feasible_solution& best_so_far,
			move_manager_type& moveman,
			termination_criteria_chain<search_type>& tc,
			abstract_cooling_schedule<search_type>& cs,
			double starting_temp,
			double K = 1.0);
    
    /// purposely not implemented (see Effective C++)
    simulated_annealing(const simulated_annealing&);
    simulated_annealing& operator=(const simulated_annealing&);
    
    /// @brief This method starts the simulated annealing search
    /// process.
    ///
    /// Remember that this is a minimization process.
    ///
    virtual void
    search()
      throw(no_moves_error);

    /// @brief The current annealing temperature.
    ///
    /// @return The current temperature of the algorithm.
    double 
    current_temp() const 
    { return current_temp_m; }

    /// @brief The annealing schedule instance.
    ///
    /// @return The cooling schedule used by this search process.
    const abstract_cooling_schedule<simulated_annealing<move_manager_type> >& 
    cooling_schedule() const
    { return cooling_schedule_m; }

  protected:
    termination_criteria_chain<simulated_annealing<move_manager_type> 
			       >& termination_criteria_m;
    abstract_cooling_schedule<simulated_annealing<move_manager_type> 
			      >& cooling_schedule_m;
    double starting_temp_m;
    double current_temp_m;
    double K_m;
#if defined (HAVE_UNORDERED_MAP) && !defined (TR1_MIXED_NAMESPACE)
    std::uniform_real<> ureal;
    std::mt19937 rng;
    std::variate_generator< std::mt19937, std::uniform_real<> > gen;
#else
    std::tr1::uniform_real<> ureal;
    std::tr1::mt19937 rng;
    std::tr1::variate_generator< std::tr1::mt19937,
				 std::tr1::uniform_real<double> > gen;
#endif
  };
    
  /// @brief Original ECS proposed by Kirkpatrick
  template<typename search_type>
  class exponential_cooling
    : public abstract_cooling_schedule<search_type>
  {
  public:
    exponential_cooling(double alpha = 0.95)
      : abstract_cooling_schedule<search_type>(), factor_m(alpha) 
    { if(alpha >= 1) throw std::runtime_error("alpha must be < 1"); }
    double
    operator()(double temp, feasible_solution& fs, search_type& ts)
    { return temp*factor_m; }
  protected:
    double factor_m;
  };

  /// @brief Alternative LCS proposed by Randelman and Grest
  template<typename search_type>
  class linear_cooling
    : public abstract_cooling_schedule<search_type>
  {
  public:
    linear_cooling(double delta = 0.1)
      : abstract_cooling_schedule<search_type>(), decrement_m(delta)
    { if(delta <= 0) throw std::runtime_error("delta must be > 0"); }
    double
    operator()(double temp, feasible_solution& fs, search_type& ts)
    { return std::max(0.0, temp-decrement_m); }
  protected:
    double decrement_m;
  };

  /// @}
}

template<typename move_manager_t>
mets::simulated_annealing<move_manager_t>::
simulated_annealing(feasible_solution& working,
		    feasible_solution& best_so_far,
		    move_manager_t& moveman,
		    termination_criteria_chain<search_type>& tc,
		    abstract_cooling_schedule<search_type>& cs,
		    double starting_temp, 
		    double K)
  : abstract_search<move_manager_t>(working, best_so_far, moveman),
    termination_criteria_m(tc), cooling_schedule_m(cs),
    starting_temp_m(starting_temp), current_temp_m(), K_m(K),
    ureal(0.0,1.0), rng(), gen(rng, ureal)
{ 
}

template<typename move_manager_t>
void
mets::simulated_annealing<move_manager_t>::search()
  throw(no_moves_error)
{
  typedef abstract_search<move_manager_t> base_t;

  typename move_manager::iterator movit;
  current_temp_m = starting_temp_m;
  while(!termination_criteria_m(base_t::working_solution_m, *this) 
        && current_temp_m >= 0.0)
    {
      gol_type actual_cost = base_t::working_solution_m.cost_function();
      gol_type best_cost = base_t::best_solution_m.cost_function();
      base_t::moves_m.refresh(base_t::working_solution_m);
      for(movit = base_t::moves_m.begin(); 
	  movit != base_t::moves_m.end(); ++movit)
	{
	  // apply move and record proposed cost function
	  gol_type cost = (*movit)->evaluate(base_t::working_solution_m);
	  
	  double delta = ((double)(cost-actual_cost));
	  if(delta < 0 || gen() < exp(-delta/(K_m*current_temp_m)))
	    {
	      // accepted: apply, record, lower temperature
	      (*movit)->apply(base_t::working_solution_m);
	      base_t::current_move_m = movit;
	      if(cost < best_cost - epsilon)
		{
		  best_cost = cost;
		  base_t::step_m = base_t::IMPROVEMENT_MADE;
		  base_t::best_solution_m = base_t::working_solution_m;
		  this->notify();
		}
	      base_t::step_m = base_t::MOVE_MADE;
	      this->notify();
	      break;
	    }
	} // end for each move
      
      current_temp_m = 
	cooling_schedule_m(current_temp_m, base_t::working_solution_m, *this);
      
    }
}
#endif
