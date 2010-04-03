// METSlib source file - termination-criteria.cc                 -*- C++ -*-
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

#include "mets.hh"

//________________________________________________________________________
bool 
mets::termination_criteria_chain::operator()(feasible_solution& fs)
{
  if(next_m)
    return next_m->operator()(fs);
  else
    return false;
}

//________________________________________________________________________
void
mets::termination_criteria_chain::reset()
{
  if(next_m) next_m->reset();
}

//________________________________________________________________________
bool 
mets::noimprove_termination_criteria::operator()(feasible_solution& fs)
{
  mets::gol_type current_cost = fs.cost_function();
  if(current_cost < best_cost_m - epsilon)
    {
      best_cost_m = current_cost;
      second_guess_m = std::max(second_guess_m, 
				(max_noimprove_m - iterations_left_m));
      iterations_left_m = max_noimprove_m;
      resets_m++;
    }

  total_iterations_m++;

  if(--iterations_left_m <= 0)
      return true;

  return termination_criteria_chain::operator()(fs);
}


