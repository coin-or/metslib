#include "mets.h"

using namespace std;

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
      int from = (p1+ii)%size;
      int to = (size+p2-ii)%size;
      assert(from >= 0 && from < size);
      assert(to >= 0 && to < size);
      sol.swap(from, to); 
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

