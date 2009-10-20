// METS lib source file - tabu-search.h                     -*- C++ -*-
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

/// @mainpage METSlib
///
/// \image html http://www.coin-or.org/images/logo/COIN-OR_150.png
/// 
/// @section Introduction
///
/// This is a library implementing some single point (not population
/// based) metaheuristics with or without memory.
///
/// The solution instance must implement mets::feasible_solution and
/// the moves must be implemented as mets::move classes.
///
/// The neighborhood can be specified implementing a mets::move_manager
///
/// All the mentioned classes must be implemented to model the problem
/// at hand.  See as an example the "tutorial" and "qap" programs.
///
/// You are also responsible of configuring and running the correct
/// algorithm.
///
/// Once your model is set up you are free of experimenting different
/// metaheuristics without changing it, but simply configuring one
/// algorith or another.
///
/// Each algorithm can be customized implementing your own decorating
/// classes, although a bunch of predefined and commonly used
/// decorators are provided with the library, some problems may need
/// customary tabu lists, termination criterias and cooling schedules.
/// 
/// The framework you must implement your model into is made of:
///
/// - mets::feasible_solution
///   - mets::permutation_problem
/// - mets::move
///   - mets::mana_move
///   - mets::swap_elements
/// - mets::move_manager
///   - mets::swap_neighborhood
///
/// The toolkit of implemented algorithms is made of:
///
/// - mets::local_search
///   - mets::move_manager
/// - mets::simulated_annealing
///   - mets::move_manager
///   - mets::abstract_cooling_schedule
///   - mets::termination_criteria_chain
///   - mets::noimprove_termination_criteria
///   - mets::threshold_termination_criteria
/// - mets::tabu_search
///   - mets::move_manager
///   - mets::tabu_list_chain
///   - mets::simple_tabu_list
///   - mets::aspiration_criteria_chain
///   - mets::best_ever_criteria
///   - mets::termination_criteria_chain
///   - mets::noimprove_termination_criteria
///   - mets::threshold_termination_criteria
///
/// To use the mets::simple_tabu_list you need to derive your moves
/// from the mets::mana_move base class and implement its pure virtual 
/// methods.
///
#ifndef METSLIB_H_
#define METSLIB_H_

#include "metslib_config.h"

#include <list>
#include <cmath>
#include <deque>
#include <limits>
#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#if defined (HAVE_UNORDERED_MAP)
#  include <unordered_map>
#  include <random>
#elif defined (HAVE_TR1_UNORDERED_MAP)
#  include <tr1/unordered_map>
#  include <tr1/random>
#else
#  error "Unable to find unordered_map header file. Please use a recent C++ compiler supporting TR1 extension."
#endif

#include "observer.h"

///
/// @brief Metaheuristic library namespace.
///
/// Framework for single point metaheuristics (Tabu Search, Simulated
/// Annealing, Iterated Local Search, Random Restart Local Search).
///
namespace mets {

  /// @brief Type of the objective/cost function.
  ///
  /// You should be able to change this to "int" for your uses
  /// to improve performance if it suffice, no guarantee.
  ///
  typedef double gol_type;

  /// @brief Exception risen when some algorithm has no more moves to
  /// make.
  class no_moves_error 
    : public std::runtime_error
  {
  public:
    no_moves_error() 
      : std::runtime_error("There are no more available moves.") {}
    no_moves_error(const std::string message) 
      : std::runtime_error(message) {}
  };

  /// @brief A sequence function object useful as an STL generator.
  ///
  /// Returns start, start+1, ... 
  ///
  class sequence
  {
  public:
    /// @brief A sequence class starting at start.
    sequence(int start = 0) 
      : value_m(start) 
    { }
    /// @brief Subscript operator. Each call increments the value of
    /// the sequence.
    int operator()() 
    { return value_m++; }
  protected:
    int value_m;
  };

  /// @defgroup model Model
  /// @{

  /// @brief interface of a feasible solution space to be searched
  /// with tabu search.
  class feasible_solution
  {
  public:

    /// @brief Virtual dtor.
    virtual
    ~feasible_solution() 
    { }

    /// @brief Cost function to be minimized.
    ///
    /// The cost function is the target that the search algorithm
    /// tries to minimize.
    ///
    /// You must implement this for your problem.
    ///
    virtual gol_type 
    cost_function() const = 0;

    /// @brief Assignment method.
    ///
    /// Needed to save the best solution so far.
    ///
    /// You must implement this for your problem.
    ///
    virtual void
    copy_from(const feasible_solution& other) = 0;

    feasible_solution& 
    operator=(const feasible_solution& other) 
    { this->copy_from(other); return *this; }
  };


  /// @brief An abstract permutation problem.
  ///
  /// The permutation problem provides a skeleton to rapidly prototype
  /// permutation problems (such as Assignment problem, Quadratic AP,
  /// TSP, and so on). The skeleton holds a pi_m variable that, at
  /// each step, contains a permutation of the numbers in [0..n-1].
  ///
  /// A few operators are provided to randomly choose a solution, to
  /// perturbate a solution with some random swaps and to simply swap
  /// two items in the list.
  ///
  /// You still need to provide your own
  /// mets::feasible_solution::cost_function() implementation.
  ///
  /// @see mets::swap_elements
  class permutation_problem: public feasible_solution 
  {
  public:
    
    /// @brief Unimplemented.
    permutation_problem(); 

    /// @brief Inizialize pi_m = {0, 1, 2, ..., n-1}.
    permutation_problem(int n) : pi_m(n)
    { std::generate(pi_m.begin(), pi_m.end(), sequence(0)); }

    /// @brief Copy from another permutation problem, if you introduce
    /// new member variables remember to override this and to call
    /// permutation_problem::copy_from in the overriding code.
    ///
    /// @param other the problem to copy from
    void copy_from(const feasible_solution& other);

    /// @brief The size of the problem
    virtual size_t 
    size() 
    { return pi_m.size(); }

    /// @brief: swap move
    ///
    /// Override this for delta evaluation of the cost function.
    virtual void
    swap(int i, int j)
    { std::swap(pi_m[i], pi_m[j]); }
    
  protected:
    std::vector<int> pi_m;

    template<typename random_generator> 
    friend void random_shuffle(permutation_problem& p, random_generator& rng);
  };


  /// @brief Shuffle a permutation problem (generates a random starting point).
  ///
  /// @see mets::permutation_problem
  template<typename random_generator>
  void random_shuffle(permutation_problem& p, random_generator& rng)
  {
    std::tr1::uniform_int<> unigen(0, p.pi_m.size());
    std::tr1::variate_generator<random_generator, 
      std::tr1::uniform_int<> >gen(rng, unigen);
    std::random_shuffle(p.pi_m.begin(), p.pi_m.end(), gen);
  }
  
  /// @brief Perturbate a problem with n swap moves.
  ///
  /// @see mets::permutation_problem
  template<typename random_generator>
  void perturbate(permutation_problem& p, unsigned int n, random_generator& rng)
  {
    std::tr1::uniform_int<> int_range;
    for(unsigned int ii=0; ii!=n;++ii) 
      {
	int p1 = int_range(rng, p.size());
	int p2 = int_range(rng, p.size());
	while(p1 == p2) 
	  p2 = int_range(rng, p.size());
	p.swap(p1, p2);
      }
  }
    


  /// @brief Move to be operated on a feasible solution.
  ///
  /// You must implement this (one or more types are allowed) for your
  /// problem.
  ///
  /// You must provide an apply as well as an unapply method.
  ///
  /// The unapply method should do the reverse of the apply or, if
  /// this is too complex, should return the solution prior to the
  /// last apply was called.
  class move
  {
  public:

    virtual 
    ~move() 
    { }; 

    ///
    /// @brief Operates this move on sol.
    ///
    virtual void
    apply(feasible_solution& sol) = 0;

    ///
    /// @brief Unapply the (last made) move.
    ///
    virtual void
    unapply(feasible_solution& sol) = 0;

    /// @brief Method usefull for tracing purposes.
    virtual void print(ostream& os) const { };
  };

  /// @brief A Mana Move is a move that can be automatically made tabu
  /// by the mets::simple_tabu_list.
  ///
  /// If you implement this class you can use the
  /// mets::simple_tabu_list as a ready to use tabu list, but you must
  /// implement copy, operator== and provide an hash funciton.
  class mana_move : public move
  {
  public:
    /// @brief Make a copy of this move.
    virtual mana_move* 
    clone() const = 0;
    
    /// @brief Tell if this move equals another (for mets::simple_tabu_list)
    virtual bool 
    operator==(const mana_move& other) const = 0;
    
    /// @brief Hash signature of this move (used by mets::simple_tabu_list)
    virtual size_t
    hash() const = 0;
  };


  template<typename rngden> class swap_neighborhood; // fw decl

  /// @brief A mets::mana_move that swaps two elements in a
  /// mets::permutation_problem.
  ///
  /// Each instance swaps two specific objects.
  ///
  /// @see mets::permutation_problem, mets::mana_move
  ///
  class swap_elements : public mets::mana_move 
  {
  public:  

    /// @brief A move that swaps from and to.
    swap_elements(int from, int to) 
      : p1(std::min(from,to)), p2(std::max(from,to)) 
    { }
    
    /// @brief Virtual method that applies the move on a point
    void
    apply(mets::feasible_solution& s)
    { permutation_problem& sol = reinterpret_cast<permutation_problem&>(s);
      sol.swap(p1, p2); }
    
    /// @brief Unapply the last move: in case of a swap the inverse move
    /// is just the same swap.
    void
    unapply(mets::feasible_solution& s)
    { this->apply(s); }
    
    /// @brief A method to clone self. Needed to insert the move in a
    /// tabu list.
    mana_move* 
    clone() const 
    { return new swap_elements(p1, p2); }
    
    /// @brief An hash function used by the tabu list (the hash value is
    /// used to insert the move in an hash set).
    size_t
    hash() const
    { return (p1)<<16^(p2); }
    
    /// @brief Comparison operator used to tell if this move is equal to
    /// a move in the tabu list.
    bool 
    operator==(const mets::mana_move& o) const;
    
    void change(int from, int to)
    { p1 = std::min(from,to); p2 = std::max(from,to); }

  protected:
    int p1; ///< the first element to swap
    int p2; ///< the second element to swap

    template <typename> 
    friend class swap_neighborhood;
  };

  /// @brief A mets::mana_move that swaps a subsequence of elements in
  /// a mets::permutation_problem.
  ///
  /// @see mets::permutation_problem, mets::mana_move
  ///
  class invert_subsequence : public mets::mana_move 
  {
  public:  

    /// @brief A move that swaps from and to.
    invert_subsequence(int from, int to) 
      : p1(from), p2(to) 
    { }
    
    /// @brief Virtual method that applies the move on a point
    void
    apply(mets::feasible_solution& s);
    
    /// @brief Unapply the last move: in case of a swap the inverse move
    /// is just the same swap.
    void
    unapply(mets::feasible_solution& s)
    { this->apply(s); }
    
    /// @brief A method to clone self. Needed to insert the move in a
    /// tabu list.
    mana_move* 
    clone() const 
    { return new invert_subsequence(p1, p2); }
    
    /// @brief An hash function used by the tabu list (the hash value is
    /// used to insert the move in an hash set).
    size_t
    hash() const
    { return (p1)<<16^(p2); }
    
    /// @brief Comparison operator used to tell if this move is equal to
    /// a move in the tabu list.
    bool 
    operator==(const mets::mana_move& o) const;
    
    void change(int from, int to)
    { p1 = from; p2 = to; }

  protected:
    int p1; ///< the first element to swap
    int p2; ///< the second element to swap

    // template <typename> 
    // friend class invert_full_neighborhood;
  };

  
  /// @brief A complex move.
  ///
  /// A complex move is made of 2 or more moves of some type. Moves
  /// are applyed in order and unapplied in reverse order.
  ///
  /// Tip: construct the defaut instance, than add the moves you wish
  /// with the add method.
  class complex_mana_move : public mets::mana_move
  {
  protected:
    typedef std::vector<mets::mana_move*> move_list_t;
    move_list_t moves_m;

  public:
    /// @brief Construct a complex move (preallocate space for moves).
    ///
    /// @param n Number of preallocated moves
    explicit
    complex_mana_move(int n = 0) 
      : mana_move(), moves_m(n)
    {  for(move_list_t::iterator it(moves_m.begin()); it!=moves_m.end(); ++it)
	*it = 0; }

    /// @brief Copy ctor, clones all the included moves.
    ///
    /// NB: before copying a complex_mana_move be sure to have
    /// assigned valid moves to each slot.
    complex_mana_move(const complex_mana_move& o);
    
    /// @brief Dtor.
    ~complex_mana_move();
    
    /// @brief Append a new move to the list.
    ///
    /// Enlarges the move list and assigns a copy of the given move to
    /// the last position.
    ///
    /// @param m A pointer to the mets::mana_move to be added
    void
    push_back(mana_move* m)
    { moves_m.push_back(m->clone()); }

    /// @brief Returns the number of attached moves
	size_t
    size() const 
    { return moves_m.size(); }

    /// @brief Returns the pointer to the ii-th move.
    ///
    /// The pointer is returned by reference so that one
    /// can assign a new instance to it. Be sure to delete
    /// the previous pointer, if it's not null.
    mana_move*&
    operator[](unsigned int ii)
    { return moves_m[ii]; }

    /// @brief Returns a const pointer to the ii-th move.
    const mana_move*
    operator[](unsigned int ii) const
    { return moves_m[ii]; }

    /// @brief Applies all the moves at once.
    /// 
    /// If there is one not assigned move (you give 3 to the
    /// constructor, but assign only two moves, or you give != 0 to
    /// the costructor and then add moves only with the push_back) a
    /// segfault will alert you. No check is made for performance
    /// reason, be sure to have all valid moves.
    void
    apply(mets::feasible_solution& s);
    
    /// @brief Unapplies all the moves at once (in reverse order)
    /// 
    /// If there is one not assigned move (you give 3 to the
    /// constructor, but assign only two moves, or you give != 0 to
    /// the costructor and then add moves only with the push_back) a
    /// segfault will alert you. No check is made for performance
    /// reason, be sure to have all valid moves.
    void
    unapply(mets::feasible_solution& s);
    
    /// @brief Clone this complex move (cloning all the included moves)
    mana_move* 
    clone() const 
    { return new complex_mana_move(*this); }
    
    /// @brief Create an hash number xoring the hashes of the included moves
    size_t
    hash() const;

    /// @brief Compare two mets::complex_mana_moves for equality
    bool operator==(const mana_move& o) const;
  };
  
  
  /// @brief Neighborhood generator.
  ///
  /// The move manager can represent both Variable and Constant
  /// Neighborhoods.
  ///
  /// To make a constant neighborhood put moves in the moves_m queue
  /// in the constructor and implement an empty refresh() method.
  ///
  /// To make a variable neighborhood (or to selectively select
  /// feasible moves at each iteration) update the moves_m queue in
  /// the refresh() method.
  class move_manager
  {
  public:
    ///
    /// @brief Initialize the move manager with an empty list of moves
    move_manager() 
      : moves_m() 
    { }

    /// @brief Virtual destructor
    virtual 
    ~move_manager() 
    { }

    /// @brief Iterator type to iterate over moves of the neighborhood
    typedef std::deque<move*>::iterator iterator;

    /// @brief Size type
    typedef std::deque<move*>::size_type size_type;

    /// @brief Called by the various search algorithms before each
    /// iteration to update the neighborhood.
    virtual void
    refresh(feasible_solution& sol) = 0;

    /// @brief Begin iterator of available moves queue.
    virtual iterator 
    begin() 
    { return moves_m.begin(); }

    /// @brief End iterator of available moves queue.
    virtual iterator 
    end() 
    { return moves_m.end(); }

    /// @brief Size of the neighborhood.
    virtual size_type 
    size() const 
    { return moves_m.size(); }

  protected:
    std::deque<move*> moves_m; ///< The moves queue

  private:
    move_manager(const move_manager&);
  };
  

  /// @brief Generates a stochastic subset of the neighborhood.
  template<typename random_generator = std::tr1::minstd_rand0>
  class swap_neighborhood : public mets::move_manager
  {
  public:
    /// @brief A neighborhood exploration strategy for mets::swap_elements.
    ///
    /// This strategy selects *moves* random swaps and *complex_moves*
    /// random double swaps.
    ///
    /// @param r a random number generator (e.g. an instance of
    /// std::tr1::minstd_rand0 or std::tr1::mt19936)
    ///
    /// @param moves the number of swaps to add to the exploration
    ///
    /// @param complex_moves the number of random double swaps to add
    /// to the exploration
    ///
    swap_neighborhood(random_generator& r, 
		      unsigned int moves, 
		      unsigned int complex_moves);

    /// @brief Dtor.
    ~swap_neighborhood();

    /// @brief Selects a different set of moves at each iteration.
    void refresh(mets::feasible_solution& s);
    
  protected:
    random_generator& rng;
    std::tr1::uniform_int<> int_range;
    unsigned int n;
    unsigned int nc;

    void randomize_move(swap_elements& m, unsigned int size);
  };

  /// @brief Generates a the full swap neighborhood.
  class swap_full_neighborhood : public mets::move_manager
  {
  public:
    /// @brief A neighborhood exploration strategy for mets::swap_elements.
    ///
    /// This strategy selects *moves* random swaps and *complex_moves*
    /// random double swaps.
    ///
    /// @param r a random number generator (e.g. an instance of
    /// std::tr1::minstd_rand0 or std::tr1::mt19936)
    ///
    /// @param moves the number of swaps to add to the exploration
    ///
    /// @param complex_moves the number of random double swaps to add
    /// to the exploration
    ///
    swap_full_neighborhood(int size) : move_manager()
    {
      for(int ii(0); ii!=size-1; ++ii)
	for(int jj(ii+1); jj!=size; ++jj)
	  moves_m.push_back(new swap_elements(ii,jj));
    } 

    /// @brief Dtor.
    ~swap_full_neighborhood() { }

    /// @brief Selects a different set of moves at each iteration.
    void refresh(mets::feasible_solution& s) { }

  };

  /// @brief Generates a the full subsequence inversion neighborhood.
  class invert_full_neighborhood : public mets::move_manager
  {
  public:
    invert_full_neighborhood(int size) : move_manager()
    {
      for(int ii(0); ii!=size; ++ii)
	for(int jj(0); jj!=size; ++jj)
	  if(ii != jj)
	    moves_m.push_back(new invert_subsequence(ii,jj));
    } 

    /// @brief Dtor.
    ~invert_full_neighborhood() { }

    /// @brief Selects a different set of moves at each iteration.
    void refresh(mets::feasible_solution& s) { }

  };

  /// @}

  /// @brief Functor class to permit hash_set of moves (used by tabu list)
  class mana_move_hash 
  {
  public:
    size_t operator()(mana_move const* mov) const 
    {return mov->hash();}
  };
  
  /// @brief Functor class to permit hash_set of moves (used by tabu list)
  template<typename Tp>
  struct dereferenced_equal_to 
  {
    bool operator()(const Tp l, 
		    const Tp r) const 
    { return *l == *r; }
  };

  class abstract_search;

  /// @defgroup common Common pieces
  /// @{

  /// @brief Function object expressing a
  /// termination criteria
  ///
  /// The tabu-search loop ends when the termination
  /// criteria is met.
  class termination_criteria_chain
  {
  public:
    /// @brief Constructor.
    /// 
    /// @param next Optional next criterium in the chain.
    explicit
    termination_criteria_chain(termination_criteria_chain* next = 0)
      : next_m(next) 
    { }
    /// purposely not implemented (see Effective C++)
    termination_criteria_chain(const termination_criteria_chain& other);
    termination_criteria_chain& 
    operator=(const termination_criteria_chain& other);

    /// @brief Virtual destructor.
    virtual 
    ~termination_criteria_chain() 
    { }

    /// @brief The function that decides if we shoud terminate the
    /// search process
    ///
    /// @param fs The current working solution.
    /// @param as The search instance.
    /// @return True if we shoud terminate
    virtual bool 
    operator()(feasible_solution& fs, abstract_search& ts);

    /// @brief Alternate function that decides if we shoud terminate the
    /// search process
    ///
    /// @param fs The current working solution.
    /// @return True if we shoud terminate
    virtual bool 
    operator()(feasible_solution& fs);

    virtual void reset() = 0;

  protected:
    termination_criteria_chain* next_m;
  };

  /// @brief An object that is called back during search process
  class search_listener : public observer<abstract_search>
  {
  public:
    /// @brief A new observer (listener) of a search process, remember
    /// to attach the created object to the search process to be
    /// observed (mets::abstract_search::attach())
    explicit
    search_listener() : observer<abstract_search>() 
    { }

    /// purposely not implemented (see Effective C++)
    search_listener(const search_listener& other);
    search_listener& 
    operator=(const search_listener& other);

    /// @brief Virtual destructor
    virtual 
    ~search_listener() 
    { }

    /// @brief This is the callback method called by searches
    /// when a move, an improvement or something else happens
    virtual void
    update(abstract_search* algorithm) = 0;
  };

  /// @}

  /// @brief An abstract search process.
  ///
  /// This has a method that should be implemented by subclasses to
  /// start the actual search.
  ///
  /// @see mets::tabu_search, mets::simulated_annealing, mets::local_search
  class abstract_search : public subject<abstract_search>
  {
  public:
    /// @brief Set some common values needed for single point
    /// metaheuristics.
    ///
    /// @param working The working solution (this will be modified
    /// during search) 
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found
    ///
    /// @param moveman A problem specific implementation of the
    /// mets::move_manager used to generate the neighborhood.
    ///
    abstract_search(feasible_solution& working,
		    feasible_solution& best_so_far,
		    move_manager& moveman)
      : subject<abstract_search>(), 
	best_solution_m(best_so_far),
	working_solution_m(working),
	moves_m(moveman),
	current_move_m(),
	step_m()
    {
      if(&working == &best_so_far)
	{
	  throw std::runtime_error("starting_point and best_so_far "
				   "must be different instances.");
	}
    }
			 
    /// purposely not implemented (see Effective C++)
    abstract_search(const abstract_search&);

    /// @brief Virtual destructor.
    virtual 
    ~abstract_search() 
    { };

    /// We just made a move.
    static const int MOVE_MADE = 0;

    /// We just made a globel improvement.
    static const int IMPROVEMENT_MADE = 1;

    /// @brief This method starts the search process.
    /// 
    /// Remember that this is a minimization process.
    ///
    /// An exception mets::no_moves_error can be risen when no move is
    /// possible.
    virtual void
    search() 
      throw(no_moves_error) = 0;

    /// @brief The best solution so far.
    virtual const feasible_solution&
    best() const 
    { return best_solution_m; };

    /// @brief The current working solution.
    virtual const feasible_solution&
    working() const 
    { return working_solution_m; }

    virtual feasible_solution&
    working() 
    { return working_solution_m; }

    /// @brief The last move made
    virtual const move&
    current_move() const 
    { return **current_move_m; }

    /// @brief The last move made
    virtual move&
    current_move() 
    { return **current_move_m; }
 
    /// @brief The move manager used by this tabu search
    const move_manager& 
    get_move_manager() const 
    { return moves_m; }

    /// @brief The move manager used by this tabu search
    move_manager& 
    get_move_manager() 
    { return moves_m; }

    /// @brief The current step of the algorithm
    ///        for use of the observers.
    ///        
    /// When you implement a new type of search you should set step_m
    /// protected variable to the status of the algorithm
    /// ("MOVE_MADE", "IMPROVEMENT_MADE", etc.).
    virtual int
    step() const 
    { return step_m; }

    /// @brief Best solution cost so far.
    virtual gol_type
    best_cost() const 
    { return best_solution_m.cost_function(); };

  protected:
    feasible_solution& best_solution_m;
    feasible_solution& working_solution_m;
    move_manager& moves_m;
    move_manager::iterator current_move_m;
    int step_m;
  };

  /// @defgroup local_search Local Search
  /// @{

  /// @brief Local search algorithm. 
  ///
  /// With customary phase alternation
  /// and move managers generated neighborhood this can be used to do
  /// also a Random Restart Local Search, a Greedy Search,
  /// an Iterated Local Search and a Variable Neighborhood Search.
  class local_search : public mets::abstract_search
  {
  public:
    /// @brief Creates a local search instance
    ///
    /// @param working The working solution (this will be modified
    /// during search) 
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found
    ///
    /// @param moveman A problem specific implementation of the
    /// mets::move_manager used to generate the neighborhood.
    ///
    /// @param short_circuit Wether the search should stop on
    /// the first improving move or not.
    local_search(feasible_solution& starting_point,
		 feasible_solution& best_so_far,
		 move_manager& moveman,
		 bool short_circuit = false);

    /// purposely not implemented (see Effective C++)
    local_search(const local_search&);
    local_search& operator=(const local_search&);
    
    /// @brief This method starts the local search process.
    ///
    /// To have a real local search you should provide an 
    /// mets::move_manager than enumerates all feasible
    /// moves.
    ///
    virtual void
    search()
      throw(no_moves_error);

  protected:
    bool short_circuit_m;
  };

  /// @}
  
  /// @defgroup simulated_annealing Simulated Annealing
  /// @{

  /// @brief Cooling criteria (for Simulated Annealing).
  ///
  /// @see mets::simulated_annealing
  ///
  /// An abstract annealing schedule. Implementations
  /// should decide the new temperature every time the 
  /// subscript operator is called (every search iteration)
  class abstract_cooling_schedule
  {
  public:
    /// @brief Constructor
    abstract_cooling_schedule() 
    { }

    /// @brief Virtual destructor
    virtual
    ~abstract_cooling_schedule() 
    { }

    /// @brief The function that updates the SA temperature.
    ///
    /// @param temp The actual annealing temperature.
    /// @param fs The current working solution.
    /// @param as The search instance.
    /// @return The new scheduled temperature.
    virtual double
    operator()(double temp, feasible_solution& fs, abstract_search& as) = 0;
  };


  /// @brief Search by Simulated Annealing.
  class simulated_annealing : public mets::abstract_search
  {
  public:
    /// @brief Creates a search by simulated annealing instance.
    ///
    /// @param working The working solution (this will be modified
    /// during search).
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found.
    ///
    /// @param moveman A problem specific implementation of the
    /// mets::move_manager used to generate the neighborhood.
    ///
    /// @param tc The termination criteria used to terminate the
    /// search process, this is an extension to the standard Simulated
    /// Annealing: you can give a termination criteria that termiantes
    /// when temperature reaches 0.
    ///
    /// @param cs The annealing schedule that decorates this SA instance.
    ///
    /// @param starting_temp The starting SA temperature.
    simulated_annealing(feasible_solution& starting_point,
			feasible_solution& best_so_far,
			move_manager& moveman,
			termination_criteria_chain& tc,
			abstract_cooling_schedule& cs,
			double starting_temp,
			double K = 1.0);
    
    /// purposely not implemented (see Effective C++)
    simulated_annealing(const simulated_annealing&);
    simulated_annealing& operator=(const simulated_annealing&);
    
    /// @brief This method starts the simulated annealing search
    /// process.
    ///
    /// Remember that this is a minimization process.
    ///
    virtual void
    search()
      throw(no_moves_error);

    /// @brief The current annealing temperature.
    ///
    /// @return The current temperature of the algorithm.
    double 
    current_temp() const 
    { return current_temp_m; }

    /// @brief The annealing schedule instance.
    ///
    /// @return The cooling schedule used by this search process.
    const abstract_cooling_schedule& 
    cooling_schedule() const
    { return cooling_schedule_m; }

  protected:
    termination_criteria_chain& termination_criteria_m;
    abstract_cooling_schedule& cooling_schedule_m;
    double starting_temp_m;
    double current_temp_m;
    double K_m;
#if defined (HAVE_UNORDERED_MAP) && !defined (TR1_MIXED_NAMESPACE)
    std::uniform_real<> ureal;
    std::mt19937 rng;
    std::variate_generator< std::mt19937, std::uniform_real<> > gen;
#else
    std::tr1::uniform_real<> ureal;
    std::tr1::mt19937 rng;
    std::tr1::variate_generator< std::tr1::mt19937,
				 std::tr1::uniform_real<double> > gen;
#endif
  };
    
  /// @brief Original ECS proposed by Kirkpatrick
  class exponential_cooling
    : public abstract_cooling_schedule
  {
  public:
    exponential_cooling(double alpha = 0.95)
      : abstract_cooling_schedule(), factor_m(alpha) 
    { if(alpha >= 1) throw std::runtime_error("alpha must be < 1"); }
    double
    operator()(double temp, feasible_solution& fs, abstract_search& ts)
    { return temp*factor_m; }
  protected:
    double factor_m;
  };

  /// @brief Alternative LCS proposed by Randelman and Grest
  class linear_cooling
    : public abstract_cooling_schedule
  {
  public:
    linear_cooling(double delta = 0.1)
      : abstract_cooling_schedule(), decrement_m(delta)
    { if(delta <= 0) throw std::runtime_error("delta must be > 0"); }
    double
    operator()(double temp, feasible_solution& fs, abstract_search& ts)
    { return std::max(0.0, temp-decrement_m); }
  protected:
    double decrement_m;
  };

  /// @}

  /// @defgroup tabu_search Tabu Search
  /// @{

  /// @brief Function object expressing an
  /// aspiration criteria
  ///
  /// An aspiration criteria is a criteria used
  /// to override the tabu list. When the aspiration
  /// criteria is met a move is made even if it's in 
  /// the tabu-list
  ///
  /// Aspiration critera can be chained so a criteria can decorate
  /// another criteria
  class aspiration_criteria_chain
  {
  public:
    /// @brief Constructor.
    /// 
    /// @param next Optional next criteria in the chain.
    explicit
    aspiration_criteria_chain(aspiration_criteria_chain *next = 0)
      : next_m(next) 
    { }

    /// purposely not implemented (see Effective C++)
    aspiration_criteria_chain(const aspiration_criteria_chain& other);
    aspiration_criteria_chain& 
    operator=(const aspiration_criteria_chain& other);

    /// @brief Virtual destructor.
    virtual 
    ~aspiration_criteria_chain() 
    { } 

    /// @brief The function that decides if we shoud accept a tabu move
    ///
    /// @param fs The current working solution.
    /// @param as The search instance.
    /// @return True if the move is to be accepted.
    virtual bool 
    operator()(feasible_solution& fs, abstract_search& as);

  protected:
    aspiration_criteria_chain* next_m;
  };

  ///
  /// @brief An abstract tabu list
  /// 
  /// This is chainable so that tabu lists can be decorated with
  /// other tabu lists.
  class tabu_list_chain
  {
  public:
    tabu_list_chain();
    /// purposely not implemented (see Effective C++)
    tabu_list_chain(const tabu_list_chain&);
    /// purposely not implemented (see Effective C++)
    tabu_list_chain& operator=(const tabu_list_chain&);

    /// Create an abstract tabu list with a certain tenure
    explicit
    tabu_list_chain(unsigned int tenure) 
      : next_m(0), tenure_m(tenure) 
    { }

    /// @brief Create an abstract tabu list with a certain tenure and
    /// a chained tabu list that decorates this one
    tabu_list_chain(tabu_list_chain* next, unsigned int tenure) 
      : next_m(next), tenure_m(tenure) 
    { }

    /// @brief Virtual destructor
    virtual 
    ~tabu_list_chain() 
    { } 

    ///
    /// @brief Make a move tabu when starting from a certain solution.
    /// 
    /// Different implementation can remember "tenure" moves, 
    /// "tenure" solutions or some other peculiar fact that
    /// will avoid cycling.
    ///
    /// @param sol The current working solution
    /// @param mov The move to make tabu
    virtual void 
    tabu(feasible_solution& sol, move& mov) = 0;

    /// @brief True if the move is tabu for the given solution.
    ///
    /// Different implementation can remember "tenure" moves, 
    /// "tenure" solutions or some other peculiar fact that
    /// will avoid cycling. So it's not defined at this stage 
    /// if a move will be tabu or not at a certain state of the
    /// search: this depends on the implementation.
    ///
    /// @param sol The current working solution
    /// @param mov The move to make tabu
    virtual bool 
    is_tabu(feasible_solution& sol, move& mov) = 0;

    ///
    /// @brief Tenure of this tabu list.
    ///
    /// The tenure is the length of the tabu-list (the order of the
    /// tabu memory)
    ///
    virtual unsigned int
    tenure() 
    { return tenure_m; }

    ///
    /// @brief Tenure of this tabu list.
    ///
    /// @param tenure: the new tenure of the list.
    ///
    virtual unsigned int
    tenure(unsigned int tenure) = 0;

  protected:
    tabu_list_chain* next_m;
    unsigned int tenure_m;
  };
  
  ///
  /// @brief Tabu Search algorithm.
  ///
  /// This implements decorator pattern. You can build many
  /// different solvers decorating tabu_search class in different
  /// ways.
  /// 
  class tabu_search : public abstract_search
  {
  public:
    /// @brief Creates a tabu Search instance.
    ///
    /// @param starting_solution  The working solution (this
    /// will be modified during search).
    ///
    /// @param best_so_far A different solution
    /// instance used to store the best solution found.
    ///
    /// @param move_manager_inst A problem specific implementation of the
    /// mets::move_manager used to generate the neighborhood.
    ///
    /// @param tabus The tabu list used to decorate this search
    /// instance.
    ///
    /// @param aspiration The aspiration criteria to use in this tabu
    /// search.
    ///
    /// @param termination The termination criteria used to terminate the
    /// search process, this is an extension to the standard Simulated
    /// Annealing: you can give a termination criteria that termiantes
    /// when temperature reaches 0.
    ///
    tabu_search(feasible_solution& starting_solution, 
		feasible_solution& best_sol, 
		move_manager& move_manager_inst,
		tabu_list_chain& tabus,
		aspiration_criteria_chain& aspiration,
		termination_criteria_chain& termination);

    tabu_search(const tabu_search&);
    tabu_search& operator=(const tabu_search&);

    virtual 
    ~tabu_search() {}

    /// @brief This method starts the tabu search process.
    /// 
    /// Remember that this is a minimization process.
    ///
    /// An exception mets::no_moves_error is risen when no move
    /// is possible.
    void 
    search() 
      throw(no_moves_error);
    
    /// @brief The current step of the algorithm
    ///        for use of the observers.
    ///        
    /// One of 
    ///  - abstract_search::MOVE_MADE, 
    ///  - abstract_search::IMPROVEMENT_MADE,
    ///  - tabu_search::ASPIRATION_CRITERIA_MET
    int
    step() const { return step_m; }
    
    /// We just followed an aspiration criteria
    static const int ASPIRATION_CRITERIA_MET = 2;

    /// @brief The tabu list used by this tabu search
    const tabu_list_chain& 
    get_tabu_list() const { return tabu_list_m; }

    /// @brief The aspiration criteria used by this tabu search
    const aspiration_criteria_chain& 
    get_aspiration_criteria() const { return aspiration_criteria_m; }

    /// @brief The termination criteria used by this tabu search
    const termination_criteria_chain& 
    get_termination_criteria() const { return termination_criteria_m; }
  protected:
    tabu_list_chain& tabu_list_m;
    aspiration_criteria_chain& aspiration_criteria_m;
    termination_criteria_chain& termination_criteria_m;
  };

  /// @brief Simplistic implementation of a tabu-list.
  ///
  /// This class implements one of the simplest and less
  /// memory hungry tabu lists. This tabu list memorizes
  /// only the moves (not the solutions).
  ///
  /// Moves must be of mets::mana_move type.
  ///
  /// The comparison between moves is demanded to the
  /// move implementation.
  ///
  /// A mets::mana_move is tabu if it's in the tabu list by means 
  /// of its operator== and hash function.
  class simple_tabu_list 
    : public tabu_list_chain
  {
  public:
    /// @brief Ctor. Makes a tabu list of the specified tenure.
    ///
    /// @param tenure Tenure (length) of the tabu list
    simple_tabu_list(unsigned int tenure) 
      : tabu_list_chain(tenure), 
	tabu_moves_m(), 
	tabu_hash_m(tenure) {}

    /// @brief Ctor. Makes a tabu list of the specified tenure.
    ///
    /// @param tenure Tenure (length) of the tabu list
    /// @param next Next list to invoke when this returns false
    simple_tabu_list(tabu_list_chain* next, unsigned int tenure) 
      : tabu_list_chain(next, tenure), 
	tabu_moves_m(), 
	tabu_hash_m(tenure) {}

    /// @brief Destructor
    ~simple_tabu_list();

    // Q&D[
    /// @brief Tabu list iterator.
    typedef std::deque<move*>::const_iterator const_iterator;
    /// @brief Tabu list size type.
    typedef std::deque<move*>::size_type size_type;

    const_iterator begin() const 
    { return tabu_moves_m.begin(); }

    const_iterator end() const 
    { return tabu_moves_m.end(); }    
    // ]Q&D

    /// @brief Make move a tabu.
    /// 
    /// This implementation simply remembers "tenure" moves.
    ///
    /// @param sol The current working solution
    /// @param mov The move to make tabu
    void
    tabu(feasible_solution& sol, /* const */ move& mov);

    /// @brief True if the move is tabu for the given solution.
    ///
    /// This implementation considers tabu each move already made less
    /// then tenure() moves ago.
    ///
    /// @param sol The current working solution
    /// @param mov The move to make tabu
    /// @return True if this move was already made during the last
    /// tenure iterations
    bool
    is_tabu(feasible_solution& sol, move& mov);

    ///
    /// @brief Tenure of this tabu list.
    ///
    /// The tenure is the length of the tabu-list (the order of the
    /// tabu memory)
    ///
    virtual unsigned int
    tenure() 
    { return tenure_m; }

    /// @brief Change the tenure (length) of this tabu list.
    ///
    /// @param tenure: the new tenure of the list.
    ///
    unsigned int tenure(unsigned int tenure_value)
    { tenure_m = tenure_value; return tenure_m; }

  protected:
    typedef std::deque<move*> move_list_type;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    typedef std::unordered_map<
      mana_move*, // Key type
      int, //insert a move and the number of times it's present in the list
      mana_move_hash, 
      dereferenced_equal_to<mana_move*> > move_map_type;
#else
    typedef std::tr1::unordered_map<
      mana_move*, // Key type
      int, //insert a move and the number of times it's present in the list
      mana_move_hash, 
      dereferenced_equal_to<mana_move*> > move_map_type;
#endif    
    move_list_type tabu_moves_m;
    move_map_type tabu_hash_m;
  };

  /// @brief Aspiration criteria implementation.
  ///
  /// This is one of the best known aspiration criteria
  /// ready to be used in your tabu-search implementation.
  ///
  /// This aspiration criteria is met when a move
  /// (even a tabu one) would result in a global improvement.
  class best_ever_criteria 
    : public aspiration_criteria_chain
  {
  public:
    best_ever_criteria() 
      : aspiration_criteria_chain() {}
    explicit
    best_ever_criteria(aspiration_criteria_chain* next) 
      : aspiration_criteria_chain(next) {}
    bool 
    operator()(feasible_solution& fs, abstract_search& ts)
    { 
      if(fs.cost_function() < ts.best_cost())
	return true;
      else
	return aspiration_criteria_chain::operator()(fs, ts); 
    }
  };
  
  /// @}


  /// @defgroup common Common pieces
  /// @{

  /// @brief Termination criteria based on the number of iterations.
  ///
  /// This termination criteria terminates the tabu-search
  /// after a fixed number of itarations.
  class iteration_termination_criteria 
    : public termination_criteria_chain
  {
  public:
    /// @brief Ctor. Max is the number of iterations to do.
    iteration_termination_criteria(int max) 
      : termination_criteria_chain(), max_m(max), iterations_m(max) {}
    explicit
    iteration_termination_criteria(termination_criteria_chain* next, 
				   int max) 
      : termination_criteria_chain(next), max_m(max), iterations_m(max) {}
    bool 
    operator()(feasible_solution& fs, abstract_search& ts)
    { 
      if (iterations_m <= 0) 
	  return true; 

      --iterations_m;
      return termination_criteria_chain::operator()(fs, ts); 
    }
    bool 
    operator()(feasible_solution& fs)
    { 
      if (iterations_m <= 0) 
	  return true; 

      --iterations_m;
      return termination_criteria_chain::operator()(fs); 
    }
    void reset() { iterations_m = max_m; }
  protected:
    int max_m;
    int iterations_m;
  };

  /// @brief Termination criteria based on the number 
  /// of iterations without an improvement.
  ///
  /// This termination criteria terminates the tabu-search
  /// after "max" number of itarations without a single
  /// global improvement.
  class noimprove_termination_criteria 
    : public termination_criteria_chain
  {
  public:
    noimprove_termination_criteria(int max) 
      : termination_criteria_chain(),
	best_cost_m(std::numeric_limits<gol_type>::max()), 
	max_noimprove_m(max), 
	iterations_left_m(max),
	total_iterations_m(0),
	resets_m(0),
	second_guess_m(0)
    {}
    noimprove_termination_criteria(termination_criteria_chain* next,
				   int max) 
      : termination_criteria_chain(next),
	best_cost_m(std::numeric_limits<gol_type>::max()), 
	max_noimprove_m(max), 
	iterations_left_m(max),
	total_iterations_m(0),
	resets_m(0),
	second_guess_m(0)
    {}

    bool 
    operator()(feasible_solution& fs, abstract_search& ts);
    bool 
    operator()(feasible_solution& fs);
    void reset() 
    { iterations_left_m = max_noimprove_m; 
      second_guess_m = total_iterations_m = resets_m = 0; 
      best_cost_m = std::numeric_limits<gol_type>::max();
    }
    int second_guess() { return second_guess_m; }
    int iteration() { return total_iterations_m; }
    int resets() { return resets_m; }
  protected:
    gol_type best_cost_m;
    int max_noimprove_m;
    int iterations_left_m;
    int total_iterations_m;
    int resets_m;
    int second_guess_m;
  };

  /// @brief Termination criteria based on cost value
  ///
  /// This termination criteria terminates the tabu-search
  /// when a certain threshold is reached
  class threshold_termination_criteria 
    : public termination_criteria_chain
  {
  public:
    threshold_termination_criteria(gol_type level) 
      : termination_criteria_chain(),
	level_m(level) 
    { } 

    threshold_termination_criteria(termination_criteria_chain* next,
				   gol_type level) 
      : termination_criteria_chain(next),
	level_m(level) 
    { } 

    bool 
    operator()(feasible_solution& fs, abstract_search& ts)
    { 
      if(ts.best_cost() <= level_m) 
	return true; 

      return termination_criteria_chain::operator()(fs, ts); 
    }

    bool 
    operator()(feasible_solution& fs)
    { 
      if(fs.cost_function() <= level_m) 
	return true; 

      return termination_criteria_chain::operator()(fs); 
    }

    void reset() 
    { /* stateless */ };

  protected:
    gol_type level_m;
  };

  /// @}

} // namespace mets

/// @brief Operator<< for moves.
std::ostream& operator<<(std::ostream& os, const mets::move& mov);

//________________________________________________________________________
template<typename random_generator>
mets::swap_neighborhood<random_generator>::swap_neighborhood(random_generator& r, 
							     unsigned int moves, 
							     unsigned int complex_moves)
  : mets::move_manager(), rng(r), int_range(0), n(moves), nc(complex_moves)
{ 
  // n simple moves
  for(unsigned int ii = 0; ii != n; ++ii) 
    moves_m.push_back(new swap_elements(0,0));
  
  // nc double moves
  for(unsigned int ii = 0; ii != nc; ++ii) 
    {
      mets::complex_mana_move& cm = *new mets::complex_mana_move(2);
      cm[0] = new swap_elements(0,0);
      cm[1] = new swap_elements(0,0);
      moves_m.push_back(&cm);
    }
}  

template<typename random_generator>
mets::swap_neighborhood<random_generator>::~swap_neighborhood()
{
  // delete all moves
  for(iterator ii = begin(); ii != end(); ++ii)
    delete (*ii);
}

template<typename random_generator>
void
mets::swap_neighborhood<random_generator>::refresh(mets::feasible_solution& s)
{
  permutation_problem& sol = dynamic_cast<permutation_problem&>(s);
  iterator ii = begin();
  
  // the first n are simple qap_moveS
  for(unsigned int cnt = 0; cnt != n; ++cnt)
    {
      swap_elements* m = static_cast<swap_elements*>(*ii);
      randomize_move(*m, sol.size());
      ++ii;
    }
  
  // the following nc are complex_mana_moves made of 2 qap_moveS
  for(unsigned int cnt = 0; cnt != nc; ++cnt)
    {
      mets::complex_mana_move& cm = 
	static_cast<mets::complex_mana_move&>(**ii);
      for(int jj = 0; jj != 2; ++jj)
	{
	  swap_elements* m = static_cast<swap_elements*>(cm[jj]);
	  randomize_move(*m, sol.size());
	}
      ++ii;
    }
}

template<typename random_generator>
void
mets::swap_neighborhood<random_generator>::randomize_move(swap_elements& m, unsigned int size)
{
  int p1 = int_range(rng, size);
  int p2 = int_range(rng, size);
  while(p1 == p2) 
    p2 = int_range(rng, size);
  // we are friend, so we know how to handle the nuts&bolts of
  // swap_elements
  m.p1 = std::min(p1,p2); 
  m.p2 = std::max(p1,p2); 
}

#endif
