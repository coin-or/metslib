METSlib
=======

METSlib: a metaheuristic framework.
-----------------------------------

This project is under development and, althought useful, must be
reviewed to be ready for anyone to use.

METSlib is an OO (Object Oriented) metaheuristics optimization
framework in C++ designed to make easy implementing or adapting
models. The model is modular: all the implemented search algorithms
can be applied to the same model.

Once the model is implemented one can test some Tabu Search Strategies
or Simulated Annealing or other local search based search strategies.

METSlib is Open Source and is covered by the GNU GPL license or, at
your option, by the Common Public License 1.0. Commercial licensing
or custom development can be considered by the author upon request.

METSlib implements the basics of some metaheuristics algorithm:

    * Random Restart Local Search
    * Variable Neighborhood Search
    * Iterated Local Search
    * Simulated Annealing (with linear, exponential and custom cooling
      schedule)
    * Tabu Search.

In its current state, the main focus of the library is on Tabu Search,
other algorithm may have some rough edges.

To use any algorithm you must implement an objective function, a
neighborhood (move manager) and some moves.

For each algorithm you are free to use some of the already implemented
termination criteria and/os cooling schedule (for SA) and/or tabu
lists and aspiration criteria (for TS), or you can implement you own
specialized versions.

The object oriented structure was carefully thought out to be highly
reusable and the algorithm where reviewed by more than one person and
more than one time.

This OO library was inspired by the OTS library released by the
Coin-OR project.

You may want to read https://github.coin/coin-or/metslib


Complete API Documentation
--------------------------

    - https://coin-or.github.io/metslib/docs/stable/0.5/html/


Tutorial 
--------

A METSlib Tutorial is available here:
  - https://coin-or.github.io/metslib/docs/stable/0.5/metslib-tr.pdf

You can also look in the distributed examples in project
https://github.com/coin-or/metslib-examples.

Contact Information
-------------------

This library was used in different projects by different developers
and proved quite useful to implement a new model (or to adapt an old
one) without re-inventing the wheel each time you need to change the
algorithm or the neighborhood. At the same time it's young so I'll be
happy to help you while implementing the nuts and bolts of your own
model since documentation is still a work in progress.

Feel free to write an email to <mirko.maischberger@gmail.com>.


Need help? Willing to help?
---------------------------

Join the mailing list
http://list.coin-or.org/mailman/listinfo/metslib 
and start contributing


Credits
-------

I'd like to thank all the people at the Global Optimization Laboratory
(http://gol.dsi.unifi.it) for continuous support and the many useful
discussions, in particular Fabio Schoen, Bernardetta Addis and Paola
Cappanera.

The automake template was borrowed from some projects by Murray
Cumming <murrayc@usa.net> and Cedric Gustin <gustin@pcpm.ucl.ac.be>


If you use the library you should cite it in your work:
=======================================================

    - Mirko Maischberger, "COIN-OR METSlib, a Metaheuristics Framework
      in Modern C++" April 2011

    BibTex Entry:

@misc{metslib2011,
  author={Mirko Maischberger},
  title={{COIN-OR} {METSlib}, a Metaheuristics Framework
      in Modern C++},
  month={April},
  year={2011},
  howpublished = {https://coin-or.github.io/metslib/docs/stable/0.5/metslib-tr.pdf},
}

- Mirko Maischberger
