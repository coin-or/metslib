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
/// This is a library implementing some neighborhood based
/// metaheuristics with or without memory.
///
/// The solution instance must implement mets::feasible_solution and
/// the moves must be implemented as mets::move classes.
///
/// The neighborhood can be specified implementing a
/// mets::move_manager subclass or providing another class with the
/// same concept (using the move_manager can ease things, but you can
/// also provide your own custom neighorhood iterator).
///
/// All the mentioned classes must be implemented to model the problem
/// at hand.  See as an example the "tutorial" and "qap" programs.
///
/// You are also responsible of configuring and running the algorithm
/// of choice.
///
/// Once your model is set up you are free of experimenting different
/// metaheuristics without changing it, but simply configuring one
/// algorith or another.
///
/// Each algorithm can be customized implementing your own decorating
/// classes, although a bunch of predefined and commonly used
/// decorators are provided with the library, some problems may need
/// customary tabu lists, termination criterias, aspiration criteria,
/// or cooling schedules.
/// 
/// The framework you must implement your model into is made of:
///
/// - mets::feasible_solution
///   - mets::permutation_problem
/// - mets::move
///   - mets::mana_move
///   - mets::swap_elements
///
/// The toolkit of implemented algorithms is made of:
///
/// - mets::move_manager (or a class implementing the same concept)
///   - mets::swap_neighborhood
/// - mets::local_search
/// - mets::simulated_annealing
///   - mets::abstract_cooling_schedule
///   - mets::termination_criteria_chain
///   - mets::noimprove_termination_criteria
///   - mets::threshold_termination_criteria
/// - mets::tabu_search
///   - mets::tabu_list_chain
///     - mets::simple_tabu_list
///   - mets::aspiration_criteria_chain
///     - mets::best_ever_criteria
///   - mets::termination_criteria_chain
///     - mets::iteration_termination_criteria
///     - mets::noimprove_termination_criteria
///     - mets::threshold_termination_criteria
///
/// To use the mets::simple_tabu_list you need to derive your moves
/// from the mets::mana_move base class and implement the pure virtual
/// methods.
///
#ifndef METS_METS_HH_
#define METS_METS_HH_

#include "metslib_config.hh"

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
#if defined (METSLIB_HAVE_UNORDERED_MAP)
#  include <unordered_map>
#  include <random>
#elif defined (METSLIB_HAVE_TR1_UNORDERED_MAP)
#  include <tr1/unordered_map>
#  include <tr1/random>
#else
#  error "Unable to find unordered_map header file. Please use a recent C++ compiler supporting TR1 extension."
#endif


///
/// @brief METSlib Metaheuristic framework namespace.
///
/// Framework for neighborhood based metaheuristics (Tabu Search,
/// Simulated Annealing, Iterated Local Search, Random Restart Local
/// Search).
///
namespace mets {
  static const double epsilon = 1e-7;
}

#include "observer.hh"
#include "model.hh"
#include "termination-criteria.hh"
#include "abstract-search.hh"
#include "local-search.hh"
#include "tabu-search.hh"
#include "simulated-annealing.hh"


std::ostream& operator<<(std::ostream& os, const mets::printable& p);

#endif
