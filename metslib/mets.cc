// METS lib source file - mets.cc                           -*- C++ -*-
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

//________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const mets::move& mov)
{
  mov.print(os);
  return os;
}

//________________________________________________________________________
void
mets::permutation_problem::copy_from(const mets::feasible_solution& other)
{
  const mets::permutation_problem& o = 
    dynamic_cast<const mets::permutation_problem&>(other);
  pi_m = o.pi_m;
}

//________________________________________________________________________
bool
mets::swap_elements::operator==(const mets::mana_move& o) const
{
  try {
    const mets::swap_elements& other = 
      dynamic_cast<const mets::swap_elements&>(o);
    return (this->p1 == other.p1 && this->p2 == other.p2);
  } catch (std::bad_cast& e) {
    return false;
  }
}

//________________________________________________________________________

void
mets::invert_subsequence::apply(mets::feasible_solution& s)
{ 
  mets::permutation_problem& sol = 
    reinterpret_cast<mets::permutation_problem&>(s);
  int size = sol.size();
  int top = p1 < p2 ? (p2-p1+1) : (size+p2-p1+1);
  for(int ii(0); ii!=top/2; ++ii)
    {
      sol.swap((p1+ii)%size, (p2-ii)%size); 
    }
}

bool
mets::invert_subsequence::operator==(const mets::mana_move& o) const
{
  try {
    const mets::invert_subsequence& other = 
      dynamic_cast<const mets::invert_subsequence&>(o);
    return (this->p1 == other.p1 && this->p2 == other.p2);
  } catch (std::bad_cast& e) {
    return false;
  }
}

//________________________________________________________________________
mets::complex_mana_move::complex_mana_move(const mets::complex_mana_move& o) 
  : mana_move(), moves_m(o.moves_m.size())
{
  for(unsigned int ii = 0; ii != moves_m.size(); ++ii)
    {
      if(o.moves_m[ii])
	moves_m[ii] = o.moves_m[ii]->clone();
    }
}

mets::complex_mana_move::~complex_mana_move()
{
  for(move_list_t::iterator ii = moves_m.begin();
      ii != moves_m.end(); ++ii)
    {
      if(*ii) delete *ii;
    }
}

void
mets::complex_mana_move::apply(mets::feasible_solution& s)
{
  for(move_list_t::iterator ii = moves_m.begin();
      ii != moves_m.end(); ++ii)
    {
      (*ii)->apply(s);
    }
}

void
mets::complex_mana_move::unapply(mets::feasible_solution& s)
{
  for(move_list_t::reverse_iterator ii = moves_m.rbegin();
      ii != moves_m.rend(); ++ii)
    {
      (*ii)->apply(s);
    }
}

size_t
mets::complex_mana_move::hash() const
{
  size_t v = 0;
  for(move_list_t::const_iterator ii = moves_m.begin();
      ii != moves_m.end(); ++ii)
    {
      v ^= (*ii)->hash();
    }
  return v; 
}

bool
mets::complex_mana_move::operator==(const mets::mana_move& o) const
{
  try {
    const complex_mana_move& other = 
      dynamic_cast<const complex_mana_move&>(o);
    // different length?
    if(moves_m.size() != other.moves_m.size()) 
      return false;
    // have at least one different move?
    for(unsigned int ii = 0; ii != moves_m.size(); ++ii)
      if(!(*moves_m[ii] == *other.moves_m[ii]))
	return false;
  } catch (std::bad_cast&) {
    // are not of the same type?
    return false;
  }
  // if we reach, we are equal
  return true;
}

//________________________________________________________________________

bool 
mets::termination_criteria_chain::operator()(feasible_solution& fs, 
					     abstract_search& ts)
{
  if(next_m)
    return next_m->operator()(fs, ts);
  else
    return false;
}

bool 
mets::termination_criteria_chain::operator()(feasible_solution& fs)
{
  if(next_m)
    return next_m->operator()(fs);
  else
    return false;
}

bool 
mets::noimprove_termination_criteria::operator()(feasible_solution& fs, 
						 abstract_search& ts)
{
  if(ts.best_cost() < best_cost_m)
    {
      best_cost_m = ts.best_cost();
      second_guess_m = std::max(second_guess_m, 
				(max_noimprove_m - iterations_left_m));
      iterations_left_m = max_noimprove_m;
      resets_m++;
    }

  total_iterations_m++;

  if(--iterations_left_m <= 0)
      return true;

  return termination_criteria_chain::operator()(fs, ts);
}

bool 
mets::noimprove_termination_criteria::operator()(feasible_solution& fs)
{
  gol_type cost = fs.cost_function();
  if(cost < best_cost_m)
    {
      best_cost_m = cost;
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

