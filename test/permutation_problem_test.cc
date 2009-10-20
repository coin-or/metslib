#include <iostream>
#include "../metslib/mets.h"

using namespace std;

class p : public mets::permutation_problem
{
public:

  p();

  p(int n) : 
    permutation_problem(n) 
  {}

  ~p();

  mets::gol_type cost_function() const;

  friend int main();
};

p::~p() {}

mets::gol_type p::cost_function() const
{ return 0.0; }

int main()
{
  // test swap_elements
  {
    p pi(10);
    mets::swap_elements move(0,0);
    for(int ii(0); ii!=9; ++ii)
      {
	move.change(ii, ii+1);
	move.apply(pi);
      }
    
    int check[]={1,2,3,4,5,6,7,8,9,0};
    
    if(pi.pi_m != std::vector<int>(&check[0], &check[10]))
      {
	cerr << "Failed swap_elements." << endl;
	return 1;
      }
  }
  // test invert_subsequence (1)
  {
    p pi(10);
    mets::invert_subsequence move(0,9);
    move.apply(pi);

    int check[]={9,8,7,6,5,4,3,2,1,0};
    if(pi.pi_m != std::vector<int>(&check[0], &check[10]))
      {
	cerr << "Failed invert_subsequence (1)." << endl;
	return 1;
      }
  }
  // test invert_subsequence (2)
  {
    p pi(9);
    mets::invert_subsequence move(0,8);
    move.apply(pi);

    int check[]={8,7,6,5,4,3,2,1,0};

    if(pi.pi_m != std::vector<int>(&check[0], &check[9]))
      {
	cerr << "Failed invert_subsequence (2)." << endl;
	return 1;
      }
  }

  // test invert_subsequence (3)
  {
    p pi(9);
    mets::invert_subsequence move(2,5);
    move.apply(pi);

    int check[]={0,1,5,4,3,2,6,7,8};

    if(pi.pi_m != std::vector<int>(&check[0], &check[9]))
      {
	cerr << "Failed invert_subsequence (3)." << endl;
	return 1;
      }
  }

  // test invert_subsequence (4)
  {
    p pi(9);
    mets::invert_subsequence move(5,2);
    move.apply(pi);

    int check[]={7,6,5,3,4,2,1,0,8};

        for(int ii(0); ii!=9; ++ii)
          cerr << pi.pi_m[ii] << "(" << check[ii] << ") ";
        cerr << endl;

    if(pi.pi_m != std::vector<int>(&check[0], &check[9]))
      {
	cerr << "Failed invert_subsequence (4)." << endl;
	return 1;
      }
  }

  return 0;
}
