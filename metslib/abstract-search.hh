#ifndef ABSTRACT_SEARCH_HH_
#define ABSTRACT_SEARCH_HH_

namespace mets {

  /// @defgroup common Common pieces
  /// @{


  /// @brief An object that is called back during search process
  template<typename search_type>
  class search_listener : public observer<search_type>
  {
  public:
    /// @brief A new observer (listener) of a search process, remember
    /// to attach the created object to the search process to be
    /// observed (mets::search_type::attach())
    explicit
    search_listener() : observer<search_type>() 
    { }

    /// purposely not implemented (see Effective C++)
    search_listener(const search_listener<search_type>& other);
    search_listener<search_type>& 
    operator=(const search_listener<search_type>& other);

    /// @brief Virtual destructor
    virtual 
    ~search_listener() 
    { }

    /// @brief This is the callback method called by searches
    /// when a move, an improvement or something else happens
    virtual void
    update(search_type* algorithm) = 0;
  };

  /// @}


  /*
  template<typename move_manager_t>
  struct move_manager_traits {
    typedef typename move_manager_t::const_iterator const_iterator;
    typedef typename move_manager_t::iterator iterator;
    typedef typename move_manager_t::size_type size_type;
    typedef typename move_manager_t::value_type vale_type;
  };
  */

  /// @brief An abstract search process.
  ///
  /// This has a method that should be implemented by subclasses to
  /// start the actual search.
  ///
  /// @see mets::tabu_search, mets::simulated_annealing, mets::local_search
  template<typename move_manager_type>
  class abstract_search : public subject< abstract_search<move_manager_type> >
  {
  public:
    /// @brief Set some common values needed for single point
    /// metaheuristics.
    ///
    /// @param working The working solution (this will be modified
    /// during search) 
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found
    ///
    /// @param moveman A problem specific implementation of the
    /// move_manager_type used to generate the neighborhood.
    ///
    abstract_search(feasible_solution& working,
		    feasible_solution& best_so_far,
		    move_manager_type& moveman)
      : subject<abstract_search<move_manager_type> >(), 
	best_solution_m(best_so_far),
	working_solution_m(working),
	moves_m(moveman),
	current_move_m(),
	step_m()
    {
      if(&working == &best_so_far)
	{
	  throw std::runtime_error("starting_point and best_so_far "
				   "must be different instances.");
	}
    }
			 
    /// purposely not implemented (see Effective C++)
    abstract_search(const abstract_search<move_manager_type>&);

    /// @brief Virtual destructor.
    virtual 
    ~abstract_search() 
    { };

    /// We just made a move.
    static const int MOVE_MADE = 0;

    /// We just made a globel improvement.
    static const int IMPROVEMENT_MADE = 1;

    /// @brief This method starts the search process.
    /// 
    /// Remember that this is a minimization process.
    ///
    /// An exception mets::no_moves_error can be risen when no move is
    /// possible.
    virtual void
    search() 
      throw(no_moves_error) = 0;

    /// @brief The best solution so far.
    virtual const feasible_solution&
    best() const 
    { return best_solution_m; };

    /// @brief The current working solution.
    virtual const feasible_solution&
    working() const 
    { return working_solution_m; }

    virtual feasible_solution&
    working() 
    { return working_solution_m; }

    /// @brief The last move made
    virtual const move&
    current_move() const 
    { return **current_move_m; }

    /// @brief The last move made
    virtual move&
    current_move() 
    { return **current_move_m; }
 
    /// @brief The move manager used by this search
    const move_manager_type& 
    get_move_manager() const 
    { return moves_m; }

    /// @brief The move manager used by this search
    move_manager_type& 
    get_move_manager() 
    { return moves_m; }

    /// @brief The current step of the algorithm
    ///        for use of the observers.
    ///        
    /// When you implement a new type of search you should set step_m
    /// protected variable to the status of the algorithm
    /// ("MOVE_MADE", "IMPROVEMENT_MADE", etc.).
    virtual int
    step() const 
    { return step_m; }

    /// @brief Best solution cost so far.
    virtual gol_type
    best_cost() const 
    { return best_solution_m.cost_function(); };

  protected:
    feasible_solution& best_solution_m;
    feasible_solution& working_solution_m;
    move_manager_type& moves_m;
    typename move_manager_type::iterator current_move_m;
    int step_m;
  };
}
#endif
