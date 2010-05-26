// METS lib source file - abstract-search.cc                     -*- C++ -*-
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
//
// This program can be distributed, at your option, under the terms of
// the CPL 1.0 as published by the Open Source Initiative
// http://www.opensource.org/licenses/cpl1.0.php

#include "mets.hh"

mets::solution_recorder::~solution_recorder() 
{ }

bool
mets::best_ever_solution::accept(mets::feasible_solution& sol)
{
  mets::copyable_solution& s = 
    static_cast<mets::copyable_solution&>(sol);
  if(s.cost_function() < best_ever_m.cost_function())
    {
      best_ever_m.copy_from(s);
      return true;
    }
  return false;
}
