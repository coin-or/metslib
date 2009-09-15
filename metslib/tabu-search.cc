// METS lib source file - tabu-search.cc                    -*- C++ -*-
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

mets::tabu_search::tabu_search(feasible_solution& starting_solution, 
			       feasible_solution& best_sol, 
			       move_manager& move_manager_inst,
			       tabu_list_chain& tabus,
			       aspiration_criteria_chain& aspiration,
			       termination_criteria_chain& termination)
  : abstract_search(starting_solution, best_sol, move_manager_inst),
    tabu_list_m(tabus),
    aspiration_criteria_m(aspiration),
    termination_criteria_m(termination)
{}

void
mets::tabu_search::search()
  throw(no_moves_error)
{
  while(!termination_criteria_m(working_solution_m, *this))
    {
      moves_m.refresh(working_solution_m);
      
      move_manager::iterator best_movit = moves_m.end(); 
      
      gol_type best_move_cost = std::numeric_limits<gol_type>::max();
      
      for(move_manager::iterator movit = moves_m.begin(); 
	  movit != moves_m.end(); ++movit)
	{
	  
	  // apply move and record proposed cost function
	  (*movit)->apply(working_solution_m);
	  gol_type cost = working_solution_m.cost_function();

	  // save state of tabu and aspiration criteria
	  bool is_tabu = tabu_list_m.is_tabu(working_solution_m, **movit);
	  bool aspiration_criteria_met = false;
	  if(is_tabu) // not interesting if this is not a tabu move
	    aspiration_criteria_met = 
	      aspiration_criteria_m(working_solution_m, *this);
	  
	  // unapply move
	  (*movit)->unapply(working_solution_m);
	  
	  // for each non-tabu move record the best one
	  if(cost < best_move_cost)
	    {
		if(!is_tabu || aspiration_criteria_met)
		{
		  best_move_cost = cost;
		  best_movit = current_move_m = movit;
		  if(aspiration_criteria_met)
		    {
		      step_m = ASPIRATION_CRITERIA_MET;
		      this->notify();
		    }
		}
	    }
	} // end for each move
      
      if(best_movit == moves_m.end())
	throw no_moves_error();

      // do the best non tabu move (unless overridden)
      (*best_movit)->apply(working_solution_m);

      // make move tabu
      tabu_list_m.tabu(working_solution_m, **best_movit);
      
      // call listener
      step_m = MOVE_MADE;
      this->notify();
      
      // check weather this is the best ever
      if(best_move_cost < best_solution_m.cost_function())
	{
	  // best_cost_m = best_move_cost;
	  best_solution_m = working_solution_m;
	  step_m = IMPROVEMENT_MADE;
	  this->notify();
	}
      
    } // end while(!termination)
}

// chain of responsibility

void
mets::tabu_list_chain::tabu(feasible_solution& sol, /* const */ move& mov)
{
  if(next_m)
    next_m->tabu(sol, mov);
}

bool
mets::tabu_list_chain::is_tabu(feasible_solution& sol, /* const */ move& mov)
{
  if(next_m) 
    return next_m->is_tabu(sol, mov);
  else 
    return false;
}

bool 
mets::aspiration_criteria_chain::operator()(feasible_solution& fs, 
					     abstract_search& ts)
{
  if(next_m)
    return next_m->operator()(fs, ts);
  else
    return false;
}

bool 
mets::termination_criteria_chain::operator()(feasible_solution& fs, 
					     abstract_search& ts)
{
  if(next_m)
    return next_m->operator()(fs, ts);
  else
    return false;
}

mets::simple_tabu_list::~simple_tabu_list()
{ 
  for(move_map_type::iterator m = tabu_hash_m.begin(); 
      m!=tabu_hash_m.end(); ++m)
    delete m->first;
}

void
mets::simple_tabu_list::tabu(feasible_solution& sol, /* const */ move& mov)
{
  mana_move* mc = 
    dynamic_cast<mana_move&>(mov).clone();

  // This does nothing if the move was already tabu (can happen when
  // aspiration criteria is met).
  pair<move_map_type::iterator, bool> 
    insert_result = tabu_hash_m.insert(make_pair(mc, 1));

  // If it was already in the map, increase the counter
  if(!insert_result.second) 
    {
      insert_result.first->second++;
      delete mc;
      mc = insert_result.first->first;
    }
  // Always add the move at the end of the list (when aspiration
  // criteria is met a move can be present more than one time in this
  // list: this is correct, so the last made move is always the last
  // in the queue). 
  tabu_moves_m.push_back(mc);

  // Since we use the hash size, the tenure is the number of different
  // moves on the list (the tabu_moves_m can have more than tenure
  // elements)
  while(tabu_hash_m.size() > this->tenure())
    {
      // update hash map *and* list structures
      move_map_type::iterator elem = tabu_hash_m.find
	(dynamic_cast<mana_move*>(tabu_moves_m.front()));
      elem->second--;
      if(elem->second == 0) 
	{
	  mana_move* tmp = elem->first;
	  tabu_hash_m.erase(elem);
	  delete tmp;
	}
      tabu_moves_m.pop_front();
    }
  tabu_list_chain::tabu(sol, mov);
}

bool
mets::simple_tabu_list::is_tabu(feasible_solution& sol, move& mov)
{
  // hash set. very fast but requires C++ ISO TR1 extension
  // and an hash function in every move (Omega(1)).
  bool tabu = (tabu_hash_m.find(&dynamic_cast<mana_move&>(mov)) 
	       != tabu_hash_m.end());

  if(tabu)
    return true;

  return tabu_list_chain::is_tabu(sol, mov);
}

bool 
mets::noimprove_termination_criteria::operator()(feasible_solution& fs, 
						 abstract_search& ts)
{
  if(fs.cost_function() < best_cost_m)
    {
      best_cost_m = fs.cost_function();
      iterations_left_m = max_noimprove_m;
    }

  if(iterations_left_m <= 0)
      return true;

  --iterations_left_m;
  return termination_criteria_chain::operator()(fs, ts);
}

