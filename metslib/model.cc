// METSlib source file - model.cc                                -*- C++ -*-
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

using namespace std;

//________________________________________________________________________
void
mets::permutation_problem::copy_from(const mets::copyable& other)
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
mets::invert_subsequence::apply(mets::feasible_solution& s) const
{ 
  mets::permutation_problem& sol = 
    static_cast<mets::permutation_problem&>(s);
  int size = sol.size();
  int top = p1 < p2 ? (p2-p1+1) : (size+p2-p1+1);
  for(int ii(0); ii!=top/2; ++ii)
    {
      int from = (p1+ii)%size;
      int to = (size+p2-ii)%size;
      assert(from >= 0 && from < size);
      assert(to >= 0 && to < size);
      sol.apply_swap(from, to); 
    }
}

mets::gol_type
mets::invert_subsequence::evaluate(const mets::feasible_solution& s) const
{ 
  const mets::permutation_problem& sol = 
    static_cast<const mets::permutation_problem&>(s);
  int size = sol.size();
  int top = p1 < p2 ? (p2-p1+1) : (size+p2-p1+1);
  mets::gol_type eval = 0.0;
  for(int ii(0); ii!=top/2; ++ii)
    {
      int from = (p1+ii)%size;
      int to = (size+p2-ii)%size;
      assert(from >= 0 && from < size);
      assert(to >= 0 && to < size);
      eval += sol.evaluate_swap(from, to); 
    }
  return eval;
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

