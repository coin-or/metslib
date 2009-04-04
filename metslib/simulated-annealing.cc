// METS lib source file - simulated-annealing.cc            -*- C++ -*-
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
//
#include "mets.h"

using namespace std;

mets::simulated_annealing::simulated_annealing(feasible_solution& working,
					       feasible_solution& best_so_far,
					       move_manager& moveman,
					       termination_criteria_chain& tc,
					       abstract_cooling_schedule& cs,
					       double starting_temp, 
					       double K)
  : abstract_search(working, best_so_far, moveman),
    termination_criteria_m(tc), cooling_schedule_m(cs),
    starting_temp_m(starting_temp), current_temp_m(), K_m(K),
    ureal(0.0,1.0), rng(), gen(rng, ureal)
{
  
}

void
mets::simulated_annealing::search()
  throw(no_moves_error)
{
  move_manager::iterator movit;
  current_temp_m = starting_temp_m;
  while(!termination_criteria_m(working_solution_m, *this) 
	and current_temp_m >= 0.0)
    {
      gol_type actual_cost = working_solution_m.cost_function();
      moves_m.refresh(working_solution_m);
      for(movit = moves_m.begin(); movit != moves_m.end(); ++movit)
	{
	  // apply move and record proposed cost function
	  (*movit)->apply(working_solution_m);
	  
	  // record cost
	  gol_type cost = working_solution_m.cost_function();
	  
	  double delta = ((double)(cost-actual_cost));
	  if(delta < 0 || gen() < exp(-delta/(K_m*current_temp_m)))
	    {
	      current_move_m = movit;
	      if(cost < best_solution_m.cost_function())
		{
		  step_m = IMPROVEMENT_MADE;
		  best_solution_m = working_solution_m;
		  this->notify();
		}
	      step_m = MOVE_MADE;
	      this->notify();
	      break;
	    }
	  // unapply move (if break was not called)
	  (*movit)->unapply(working_solution_m);
	} // end for each move
      
      current_temp_m = 
	cooling_schedule_m(current_temp_m, working_solution_m, *this);
      
    } 
}
