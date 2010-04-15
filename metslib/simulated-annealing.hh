// METSlib source file - simulated-annealing.hh                  -*- C++ -*-
//
// Copyright (C) 2006-2010 Mirko Maischberger <mirko.maischberger@gmail.com>
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

#ifndef METS_SIMULATED_ANNEALING_HH_
#define METS_SIMULATED_ANNEALING_HH_

namespace mets {

  /// @defgroup simulated_annealing Simulated Annealing
  /// @{

  /// @brief Cooling criteria (for Simulated Annealing).
  ///
  /// @see mets::simulated_annealing
  ///
  /// An abstract annealing schedule. Implementations
  /// should decide the new temperature every time the 
  /// subscript operator is called (every search iteration)
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
    /// @return The new scheduled temperature.
    virtual double
    operator()(double temp, feasible_solution& fs) = 0;
  };

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
			solution_recorder& recorder,
			move_manager_type& moveman,
			termination_criteria_chain& tc,
			abstract_cooling_schedule& cs,
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
    const abstract_cooling_schedule& 
    cooling_schedule() const
    { return cooling_schedule_m; }

  protected:
    termination_criteria_chain& termination_criteria_m;
    abstract_cooling_schedule& cooling_schedule_m;
    double starting_temp_m;
    double current_temp_m;
    double K_m;
#if defined (METSLIB_HAVE_UNORDERED_MAP) && !defined (METSLIB_TR1_MIXED_NAMESPACE)
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
  class exponential_cooling
    : public abstract_cooling_schedule
  {
  public:
    exponential_cooling(double alpha = 0.95)
      : abstract_cooling_schedule(), factor_m(alpha) 
    { if(alpha >= 1) throw std::runtime_error("alpha must be < 1"); }
    double
    operator()(double temp, feasible_solution& fs)
    { return temp*factor_m; }
  protected:
    double factor_m;
  };

  /// @brief Alternative LCS proposed by Randelman and Grest
  class linear_cooling
    : public abstract_cooling_schedule
  {
  public:
    linear_cooling(double delta = 0.1)
      : abstract_cooling_schedule(), decrement_m(delta)
    { if(delta <= 0) throw std::runtime_error("delta must be > 0"); }
    double
    operator()(double temp, feasible_solution& fs)
    { return std::max(0.0, temp-decrement_m); }
  protected:
    double decrement_m;
  };

  /// @}
}

template<typename move_manager_t>
mets::simulated_annealing<move_manager_t>::
simulated_annealing(feasible_solution& working,
		    solution_recorder& recorder,
		    move_manager_t& moveman,
		    termination_criteria_chain& tc,
		    abstract_cooling_schedule& cs,
		    double starting_temp, 
		    double K)
  : abstract_search<move_manager_t>(working, recorder, moveman),
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

  current_temp_m = starting_temp_m;
  while(!termination_criteria_m(base_t::working_solution_m) 
        && current_temp_m > 0.0)
    {
      gol_type actual_cost = base_t::working_solution_m.cost_function();
      gol_type best_cost = base_t::solution_recorder_m.best_cost();
      base_t::moves_m.refresh(base_t::working_solution_m);
      for(typename move_manager_t::iterator movit = base_t::moves_m.begin(); 
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

	      if(base_t::solution_recorder_m.accept(base_t::working_solution_m))
		{
		  base_t::step_m = base_t::IMPROVEMENT_MADE;
		  this->notify();
		}
	      base_t::step_m = base_t::MOVE_MADE;
	      this->notify();
	      break;
	    }
	} // end for each move
      
      current_temp_m = 
	cooling_schedule_m(current_temp_m, base_t::working_solution_m);
    }
}
#endif
