// tabu list regression
#include <metslib/mets.hh>

using namespace std;

class my_sol : public mets::evaluable_solution
{
  mets::gol_type cost_function() const
  { return 0.0; }

  void copy_from(const mets::copyable&) 
  { }
};

class my_move : public mets::mana_move 
{
  int i_m;
public:
  my_move(int i) : i_m(i) 
  { }

  bool operator==(const mana_move& m) const
  { const my_move& o = static_cast<const my_move&>(m); return i_m == o.i_m; }

  my_move* clone() const
  { return new my_move(i_m); }

  size_t hash() const
  { return i_m; }

  void apply(mets::feasible_solution&) const {}
  mets::gol_type evaluate(const mets::feasible_solution&) const { return 0.0; }

};

int main(void)
{
  // test basic correct tabu list behaviour with many different moves
  {
    const int tenure = 7;
    const int tests = 10000;
    
    my_sol s;
    mets::simple_tabu_list tl(tenure);
    
    for(int ii = 0; ii != tests; ++ii)
      {
	my_move m(ii);
	tl.tabu(s, m);
	for(int jj = 0; jj != tests; ++jj)
	  {
	    my_move tm(jj);
	    if(jj > ii-tenure && jj <=ii)
	      {
		if(!tl.is_tabu(s, tm))
		  {
		    cerr << "Failure at ! " << ii << ", " << jj << endl;
		    return 1;
		  }
	      }
	    else
	      {
		if(tl.is_tabu(s, tm))
		  {
		    cerr << "Failure at " << ii << ", " << jj << endl;
		    return 1;
		  }
	      }
	  }
      }
  }

  // test correct tabu list behaviour with duplicated moves
  {
    const int tenure = 3;
    mets::simple_tabu_list tl(tenure);

    my_sol s;
    my_move m1(1);
    tl.tabu(s, m1);
    if(!tl.is_tabu(s, m1)) 
      {
	cerr << "Err1" <<endl;
	return 1;
      }
    my_move m2(2);
    tl.tabu(s, m2);
    tl.tabu(s, m2);
    tl.tabu(s, m2);
    my_move m3(3);
    tl.tabu(s, m3);
    tl.tabu(s, m3);
    tl.tabu(s, m3);
    if(!tl.is_tabu(s, m1)) 
      {
	cerr << "Err2" <<endl;
	return 1;
      }
    my_move m4(4);
    tl.tabu(s, m4);
    if(tl.is_tabu(s, m1)) 
      {
	cerr << "Err3" <<endl;
	return 1;
      }
  }

  cerr << "Success!" << endl;
  return 0;
}
