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
//
// This program can be distributed, at your option, under the terms of
// the CPL 1.0 as published by the Open Source Initiative
// http://www.opensource.org/licenses/cpl1.0.php


#include "mets.hh"

// chain of responsibility

void
mets::tabu_list_chain::tabu(feasible_solution& sol, /* const */ move& mov)
{
  if(next_m)
    next_m->tabu(sol, mov);
}

bool
mets::tabu_list_chain::is_tabu(feasible_solution& sol, /* const */ move& mov) const
{
  if(next_m) 
    return next_m->is_tabu(sol, mov);
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
    dynamic_cast<mana_move&>(mov).opposite_of();

  // This does nothing if the move was already tabu (can happen when
  // aspiration criteria is met).
  std::pair<move_map_type::iterator, bool> 
    insert_result = tabu_hash_m.insert(std::make_pair(mc, 1));

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
mets::simple_tabu_list::is_tabu(feasible_solution& sol, move& mov) const
{
  // hash set. very fast but requires C++ ISO TR1 extension
  // and an hash function in every move (Omega(1)).
  bool tabu = (tabu_hash_m.find(&dynamic_cast<mana_move&>(mov)) 
	       != tabu_hash_m.end());

  if(tabu)
    return true;

  return tabu_list_chain::is_tabu(sol, mov);
}

//////////////////////////////////////////////////////////////////////////
// aspiration_criteria_chain
void 
mets::aspiration_criteria_chain::reset()
{
  if(next_m)
    return next_m->reset();
}

void 
mets::aspiration_criteria_chain::accept(feasible_solution& fs, 
					move& mov)
{
  if(next_m) next_m->accept(fs, mov);
}

bool 
mets::aspiration_criteria_chain::operator()(feasible_solution& fs, 
					    move& mov) const
{
  if(next_m)
    return next_m->operator()(fs, mov);
  else
    return false;
}

//////////////////////////////////////////////////////////////////////////
// best_ever_criteria
mets::best_ever_criteria::best_ever_criteria(double tolerance) 
  : aspiration_criteria_chain(),
    best_m(std::numeric_limits<gol_type>::max()),
    tolerance_m(tolerance)
{ }

mets::best_ever_criteria::best_ever_criteria(aspiration_criteria_chain* next, double tolerance) 
  : aspiration_criteria_chain(next),
    best_m(std::numeric_limits<gol_type>::max()),
    tolerance_m(tolerance)
{ }
    
void mets::best_ever_criteria::reset()
{
  best_m = std::numeric_limits<mets::gol_type>::max();
  aspiration_criteria_chain::reset();
}

void
mets::best_ever_criteria::accept(feasible_solution& fs, move& mov) 
{
  best_m = std::min(dynamic_cast<const evaluable_solution&>(fs).cost_function(), best_m);
  aspiration_criteria_chain::accept(fs, mov);
}  

bool 
mets::best_ever_criteria::operator()(feasible_solution& fs, move& mov) const
{ 
  /// the solution is the solution before applying mov.
  if(mov.evaluate(fs) < best_m - tolerance_m)
    return true;
  else
    return aspiration_criteria_chain::operator()(fs, mov); 
}
