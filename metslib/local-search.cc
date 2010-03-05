// METS lib source file - local-search.cc                   -*- C++ -*-
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

#include "mets.h"

using namespace std;

mets::local_search::local_search(feasible_solution& working,
				 feasible_solution& best_so_far,
				 move_manager& moveman,
				 bool short_circuit)
  : abstract_search(working, best_so_far, moveman),
    short_circuit_m(short_circuit)
{ 
  step_m = 0; 
}

void
mets::local_search::search()
  throw(no_moves_error)
{
  {
    move_manager::iterator best_movit;
    do
      {
	moves_m.refresh(working_solution_m);
	best_movit = moves_m.end();
	gol_type best_cost = best_solution_m.cost_function();
	for(move_manager::iterator movit = moves_m.begin();
	    movit != moves_m.end(); ++movit)
	  {
	    // evaluate the cost after the move
	    gol_type cost = (*movit)->evaluate(working_solution_m);
	    if(cost < best_cost)
	      {
		best_cost = cost;
		best_movit = movit;
		if(short_circuit_m) break;
	      }
	  } // end for each move
	
	if(best_movit != moves_m.end()) 
	  {
	    (*best_movit)->apply(working_solution_m);
	    best_solution_m = working_solution_m;
	    current_move_m = best_movit;
	    this->notify();
	  }

      } while(best_movit != moves_m.end());
  }
}
