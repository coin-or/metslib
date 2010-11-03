// termination criteria regression
#include <metslib/mets.hh>

using namespace std;

class zero_sol : public mets::copyable_solution
{
  mets::gol_type cost_function() const
  { return 0.0; }

  void copy_from(const mets::copyable&) 
  { }
};

int main(void)
{
  zero_sol s;

  int max = 1972;
  int count = 0;
  mets::iteration_termination_criteria years(max);

  while(!years(s)) count++;
  if(count != max) 
    {
      cerr << "Failed max iteration test." << endl;
      return -1;
    }

  int noimprove = 42;
  mets::noimprove_termination_criteria days(noimprove);
  count = 0;
  while(!days(s)) count++;
  if(count != noimprove || days.iteration() != noimprove) 
    {
      cerr << "Second guess: " << days.second_guess() << endl;
      cerr << "Iterations: " << days.iteration() << "!=" << count << endl;
      cerr << "Failed max no-improve test." << endl;
      return -1;
    }

  cerr << "Success!" << endl;
  return 0;
}
