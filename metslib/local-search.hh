// METS lib source file - local-search.hh                   -*- C++ -*-
//
//
// Copyright (C) 2006-2008 Mirko Maischberger <mirko.maischberger@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef LOCAL_SEARCH_HH_
#define LOCAL_SEARCH_HH_

namespace mets {
  /// @defgroup local_search Local Search
  /// @{

  /// @brief Local search algorithm. 
  ///
  /// With customary phase alternation
  /// and move managers generated neighborhood this can be used to do
  /// also a Random Restart Local Search, a Greedy Search,
  /// an Iterated Local Search and a Variable Neighborhood Search.
  template<typename move_manager_type>
  class local_search : public mets::abstract_search<move_manager_type>
  {
  public:
    /// @brief Creates a local search instance
    ///
    /// @param working The working solution (this will be modified
    /// during search) 
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found
    ///
    /// @param moveman A problem specific implementation of the
    /// move_manager_type concept used to generate the neighborhood.
    ///
    /// @param short_circuit Wether the search should stop on
    /// the first improving move or not.
    local_search(feasible_solution& starting_point,
		 feasible_solution& best_so_far,
		 move_manager_type& moveman,
		 bool short_circuit = false);

    /// purposely not implemented (see Effective C++)
    local_search(const local_search&);
    local_search& operator=(const local_search&);
    
    /// @brief This method starts the local search process.
    ///
    /// To have a real local search you should provide an 
    /// move_manager_type than enumerates all feasible
    /// moves.
    ///
    virtual void
    search()
      throw(no_moves_error);

  protected:
    bool short_circuit_m;
  };

  /// @}
  
  /// @defgroup simulated_annealing Simulated Annealing
  /// @{

  /// @brief Cooling criteria (for Simulated Annealing).
  ///
  /// @see mets::simulated_annealing
  ///
  /// An abstract annealing schedule. Implementations
  /// should decide the new temperature every time the 
  /// subscript operator is called (every search iteration)
  template<typename search_type>
  class abstract_cooling_schedule
  {
  public:
    /// @brief Constructor
    abstract_cooling_schedule() 
    { }

    /// @brief Virtual destructor
    virtual
    ~abstract_cooling_schedule() 
    { }

    /// @brief The function that updates the SA temperature.
    ///
    /// @param temp The actual annealing temperature.
    /// @param fs The current working solution.
    /// @param as The search instance.
    /// @return The new scheduled temperature.
    virtual double
    operator()(double temp, feasible_solution& fs, search_type& as) = 0;
  };
}

template<typename move_manager_t>
mets::local_search<move_manager_t>::local_search(feasible_solution& working,
						 feasible_solution& best_so_far,
						 move_manager_t& moveman,
						 bool short_circuit)
  : abstract_search<move_manager_t>(working, best_so_far, moveman),
    short_circuit_m(short_circuit)
{ 
  typedef abstract_search<move_manager_t> base_t;
  base_t::step_m = 0; 
}

template<typename move_manager_t>
void
mets::local_search<move_manager_t>::search()
  throw(no_moves_error)
{
  typedef abstract_search<move_manager_t> base_t;
  {
    typename move_manager_t::iterator best_movit;
    do
      {
	base_t::moves_m.refresh(base_t::working_solution_m);
	best_movit = base_t::moves_m.end();
	gol_type best_cost = base_t::best_solution_m.cost_function();
	for(typename move_manager::iterator movit = base_t::moves_m.begin();
	    movit != base_t::moves_m.end(); ++movit)
	  {
	    // evaluate the cost after the move
	    gol_type cost = (*movit)->evaluate(base_t::working_solution_m);
	    if(cost < best_cost - epsilon)
	      {
		best_cost = cost;
		best_movit = movit;
		if(short_circuit_m) break;
	      }
	  } // end for each move
	
	if(best_movit != base_t::moves_m.end()) 
	  {
	    (*best_movit)->apply(base_t::working_solution_m);
	    base_t::best_solution_m = base_t::working_solution_m;
	    base_t::current_move_m = best_movit;
	    this->notify();
	  }

      } while(best_movit != base_t::moves_m.end());
  }
}
#endif