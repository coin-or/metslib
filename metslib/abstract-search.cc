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
