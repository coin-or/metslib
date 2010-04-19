// METSlib source file - termination-criteria.hh                 -*- C++ -*-
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

#ifndef METS_TERMINATION_CRITERIA_HH_
#define METS_TERMINATION_CRITERIA_HH_

namespace mets {
 
  /// @defgroup common Termination criteria
  /// @{

  /// @brief Function object expressing a termination criteria
  ///
  /// The search loop ends when the termination criteria is met.
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
    termination_criteria_chain(const termination_criteria_chain&);
    termination_criteria_chain& operator=(const termination_criteria_chain&);

    /// @brief Virtual destructor.
    virtual 
    ~termination_criteria_chain() 
    { }

    /// @brief Alternate function that decides if we shoud terminate the
    /// search process
    ///
    /// (chain of responsibility)
    ///
    /// @param fs The current working solution.
    /// @return True if we shoud terminate
    virtual bool 
    operator()(feasible_solution& fs);

    /// @brief Reset the criterion to its initial state.
    ///
    /// (chain of responsibility)
    ///
    virtual void reset();

  protected:
    termination_criteria_chain* next_m;
  };

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
      : termination_criteria_chain(), 
	max_m(max), 
	iterations_m(max) {}

    explicit
    iteration_termination_criteria
    (termination_criteria_chain* next, int max) 
      : termination_criteria_chain(next), 
	max_m(max), 
	iterations_m(max) {}

    bool 
    operator()(feasible_solution& fs)
    { 
      if (iterations_m <= 0) 
	return true; 
      
      --iterations_m;
      return termination_criteria_chain::operator()(fs); 
    }

    void 
    reset() 
    { iterations_m = max_m; termination_criteria_chain::reset(); }

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

    noimprove_termination_criteria
    (termination_criteria_chain* next, int max) 
      : termination_criteria_chain(next),
	best_cost_m(std::numeric_limits<gol_type>::max()), 
	max_noimprove_m(max), 
	iterations_left_m(max),
	total_iterations_m(0),
	resets_m(0),
	second_guess_m(0)
    { }

    bool 
    operator()(feasible_solution& fs);
    void reset() 
    { iterations_left_m = max_noimprove_m; 
      second_guess_m = total_iterations_m = resets_m = 0; 
      best_cost_m = std::numeric_limits<gol_type>::max();
      termination_criteria_chain::reset();      
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

    threshold_termination_criteria
    (termination_criteria_chain* next, gol_type level) 
      : termination_criteria_chain(next),
	level_m(level) 
    { } 

    bool 
    operator()(feasible_solution& fs)
    { 
      if(fs.cost_function() <= level_m) 
	return true; 
      
      return termination_criteria_chain::operator()(fs); 
    }

    void reset() 
    { termination_criteria_chain::reset(); }
    
  protected:
    gol_type level_m;
  };

  /// @}
}

#endif
