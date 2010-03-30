// METS lib source file - mets.h                               -*- C++ -*-
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

/// @mainpage METSlib
///
/// \image html http://www.coin-or.org/images/logo/COIN-OR_150.png
/// 
/// @section Introduction
///
/// This is a library implementing some single point (not population
/// based) metaheuristics with or without memory.
///
/// The solution instance must implement mets::feasible_solution and
/// the moves must be implemented as mets::move classes.
///
/// The neighborhood can be specified implementing a mets::move_manager
///
/// All the mentioned classes must be implemented to model the problem
/// at hand.  See as an example the "tutorial" and "qap" programs.
///
/// You are also responsible of configuring and running the correct
/// algorithm.
///
/// Once your model is set up you are free of experimenting different
/// metaheuristics without changing it, but simply configuring one
/// algorith or another.
///
/// Each algorithm can be customized implementing your own decorating
/// classes, although a bunch of predefined and commonly used
/// decorators are provided with the library, some problems may need
/// customary tabu lists, termination criterias and cooling schedules.
/// 
/// The framework you must implement your model into is made of:
///
/// - mets::feasible_solution
///   - mets::permutation_problem
/// - mets::move
///   - mets::mana_move
///   - mets::swap_elements
/// - mets::move_manager
///   - mets::swap_neighborhood
///
/// The toolkit of implemented algorithms is made of:
///
/// - mets::local_search
///   - mets::move_manager
/// - mets::simulated_annealing
///   - mets::move_manager
///   - mets::abstract_cooling_schedule
///   - mets::termination_criteria_chain
///   - mets::noimprove_termination_criteria
///   - mets::threshold_termination_criteria
/// - mets::tabu_search
///   - mets::move_manager
///   - mets::tabu_list_chain
///   - mets::simple_tabu_list
///   - mets::aspiration_criteria_chain
///   - mets::best_ever_criteria
///   - mets::termination_criteria_chain
///   - mets::noimprove_termination_criteria
///   - mets::threshold_termination_criteria
///
/// To use the mets::simple_tabu_list you need to derive your moves
/// from the mets::mana_move base class and implement its pure virtual 
/// methods.
///
#ifndef METSLIB_H_
#define METSLIB_H_

#include "metslib_config.h"

#include <list>
#include <cmath>
#include <deque>
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <typeinfo>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#if defined (HAVE_UNORDERED_MAP)
#  include <unordered_map>
#  include <random>
#elif defined (HAVE_TR1_UNORDERED_MAP)
#  include <tr1/unordered_map>
#  include <tr1/random>
#else
#  error "Unable to find unordered_map header file. Please use a recent C++ compiler supporting TR1 extension."
#endif

static const double epsilon = 1e-7;

#include "observer.h"
#include "model.hh"
#include "termination-criteria.hh"
#include "abstract-search.hh"
#include "local-search.hh"
#include "tabu-search.hh"
#include "simulated-annealing.hh"

///
/// @brief Metaheuristic library namespace.
///
/// Framework for single point metaheuristics (Tabu Search, Simulated
/// Annealing, Iterated Local Search, Random Restart Local Search).
///
namespace mets { } 

/// @brief Operator<< for moves.
std::ostream& operator<<(std::ostream& os, const mets::move& mov);

/*
//________________________________________________________________________
template<typename random_generator>
mets::swap_neighborhood< random_generator
			 >::swap_neighborhood(random_generator& r, 
					      unsigned int moves)
  : mets::move_manager(), rng(r), int_range(0), n(moves)
{ 
  // n simple moves
  for(unsigned int ii = 0; ii != n; ++ii) 
    moves_m.push_back(new swap_elements(0,0));
}  

template<typename random_generator>
mets::swap_neighborhood<random_generator>::~swap_neighborhood()
{
  // delete all moves
  for(iterator ii = begin(); ii != end(); ++ii)
    delete (*ii);
}

template<typename random_generator>
void
mets::swap_neighborhood<random_generator>::refresh(mets::feasible_solution& s)
{
  permutation_problem& sol = dynamic_cast<permutation_problem&>(s);
  iterator ii = begin();
  
  // the first n are simple qap_moveS
  for(unsigned int cnt = 0; cnt != n; ++cnt)
    {
      swap_elements* m = static_cast<swap_elements*>(*ii);
      randomize_move(*m, sol.size());
      ++ii;
    }
  
}

template<typename random_generator>
void
mets::swap_neighborhood<random_generator
			>::randomize_move(swap_elements& m, unsigned int size)
{
  int p1 = int_range(rng, size);
  int p2 = int_range(rng, size);
  while(p1 == p2) 
    p2 = int_range(rng, size);
  // we are friend, so we know how to handle the nuts&bolts of
  // swap_elements
  m.p1 = std::min(p1,p2); 
  m.p2 = std::max(p1,p2); 
}
*/
#endif
