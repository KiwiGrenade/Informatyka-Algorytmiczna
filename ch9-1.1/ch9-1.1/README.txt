------------------------------------------------------------
* 9th DIMACS Implementation Challenge: Shortest Paths
* http://www.dis.uniroma1.it/~challenge9

* Change log:   $Date: 2006/02/21 22:20:12 $
* Changed by:   $Author: irene $
* Revision:     $Revision: 1.10 $
------------------------------------------------------------

DIMACS Challenge 9 Benchmark Platform
Version 1.1
October 30, 2006

This directory contains the core experimental package for
the 9th DIMACS Implementation Challenge.

(C) 2005-2006 Camil Demetrescu, Andrew V. Goldberg, David S. Johnson

-------------------------------------------------------------
LICENSE

Unless otherwise stated, all programs in this package are 
distributed under the GNU General Public License (GPL),
Version 2, June 1991. Please see included file LICENSE.txt.

-------------------------------------------------------------
REPOSITORY STRUCTURE

  - README.txt: this file

  - LICENSE.txt: license statement

  - Makefile: script that builds the code, generates the test
              instances, and runs core experiments.

  - docs : documentation
         |
         +- families: description of problem families
         |
         +- format:   description of file formats
         |
         +- solvers:  shortest path algorithms benchmark
                      implementations

  - gens : synthetic problem instance generators
         |
         +- grid:     generator of grid graphs
         |
         +- local_q:  generator of p2p query pairs with a given
         |            distance in the graph (different degr of locality)
         |
         +- rand:     generator of random graphs
         |
         +- tor:      generator of torus-embedded grids
         |
         +- utils:    utility generators

  - inputs : created by the generators; core instances are 
             generated here (synthetic and real-world)

  - lib : libraries used in the code

  - results : created by experim. drivers; performance measure
              report files are generated here

  - scripts : scripts for generating the synthetic test sets and
              running core experiments

  - solvers : benchmark shortest path codes
            |
            +- mlb-dimacs: shortest path solvers for ss and p2p
            |
            +- neg: solvers for instances with negative weights

  - utils : utility programs for converting/manipulating test sets
          | 
          +- cutter: program that cuts a TIGER/Line graph along a
          |          given bounding box + program that renumbers
          |          node IDs so that the are consecutive
          |
          +- merger: merges one or more TIGER/Line files
          |
          +- maxcc:  routines for extracting the largest connected
                     component of a TIGER/Line graph

-------------------------------------------------------------
PLATFORM REQUIREMENTS

The following instructions apply to most UNIX-based environments. We 
have successfully tested the package on a number of platforms, 
including Linux, MacOS X, and Cygwin. We expect it to be easily 
portable across any platform with a POSIX interface, a Perl 
interpreter, and a C/C++ compiler. Your platform must be equipped
with a recent version of the ftp program (able to handle http
requests).

-------------------------------------------------------------
HOW TO BUILD THE PACKAGE

To build the package, you have to:

1) compile the code for generators, solvers and utilities ('make' command)
2) generate input instances ('make gen' command)
3) run the solvers to create performance reports ('make run' command)

Steps 2) and 3) can be specialized for ss or p2p for people who are only 
interested in a specific problem (e.g., 'make gen_ss', 'make gen_p2p', 
'make run_ss', 'make run_p2p'). Please find more detailed instructions
below.

-------------------------------------------------------------
1) HOW TO COMPILE THE CODE

To compile the code, just go to directory ch9 and type 'make'. This will 
build the code for generators, solvers and utilities.

-------------------------------------------------------------
2) HOW TO CREATE THE CORE INSTANCES

To build the core instances, just type 'make gen'. This will create in
directory ch9/inputs all problem families. Those include both
synthetic and real-world instances. Synthetic instances are built
by the generators located in the ch9/gens directory. Real-world instances
are downloaded from the Challenge server running on www.dis.uniroma1.it.

To run 'make gen', you must have built the package first 
(see section HOW TO COMPILE THE CODE above).

INSTALL NOTES: 

* the platform building process may take a while, especially to generate 
  local query files for p2p problems. Please be patient. 

* to install real-world core families, the 'make gen' command 
  requires that you are connected to the Internet and can run ftp.
  The installer assumes your ftp program can use the http protocol.
  Old versions of ftp do not support http and may not work: for instance, 
  this happens with some releases of Cygwin. In this case, you have to 
  download files manually with an http client from:

  http://www.dis.uniroma1.it/~challenge9/data/USA-road-d
  http://www.dis.uniroma1.it/~challenge9/data/USA-road-t

  Downloaded files should be put in ch9/inputs/USA-road-d and in
  ch9/inputs/USA-road-t.

* core instances require around 11GB of free disk space
  (5.2GB for real-world families USA-road-d and USA-road-t).

IMPORTANT NOTICE: 

Building and running the whole package may require several hours.
If you are only interested in a specific problem, you can generate only 
instances for that problem. If you are only interested in the ss 
problem, you can type:

'make gen_gr' to create the graphs (both synthetic and real-world)
'make gen_ss' to create the synthetic ss instances

If you are only interested in the p2p problem, you can type:

'make gen_gr' to create the synthetic graphs
'make gen_p2p' to create the synthetic p2p instances (this may take a while)

You can refine your control over the building process even further.
For instance, if you wish to generate graphs in the USA-road-d family and 
the related problem instances only, you can go to ch9/scripts and type:

'perl genUSA-road-d.gr.pl'      (download graphs from the server)
'perl genUSA-road-d.ss.pl'      (generate ss problem instances)
'perl genUSA-road-d.rnd.p2p.pl' (generate random query pairs)
'perl genUSA-road-d.loc.p2p.pl' (generate local query pairs)

Please refer to ch9/scripts/README.txt for further information about 
customizing the instance generation.

-------------------------------------------------------------
3) HOW TO RUN THE CORE EXPERIMENTS

To run the benchmark solvers on all core input families, type
'make run'. You must have created all core instances first. 
Performance report files are generated in the ch9/results directory.

If you are only interested in the ss problem, you can type:
'make run_ss'. If you are only interested in the p2p problem, you 
can type: 'make run_p2p'. 

You can refine your control over the running process even further.
For instance, if you wish to run ss experiments on graphs in the 
USA-road-d family only, you can go to ch9/scripts and type:
'perl runUSA-road-d.ss.pl'.

Please refer to ch9/scripts/README.txt for further information about
running only selected experiments.

NOTE:

The running times of benchmark solvers on core input families 
should be used to normalize the running times of your algorithms.

For instance, the measure Time(your code)/Time(benchmark solver) is
less platform-dependent than Time(your algorithm), allowing direct 
comparisons of performance measures collected on different platforms. 
While such comparisons may not be very accurate because of 
architectural differences between platforms (e.g., memory 
hierarchy, etc.), they would still capture relevant performance 
differences of different algorithms on the same input.

------------------------------------------------------------

For questions and feedback, please write to goldberg@microsoft.com.

Enjoy!
Camil, Andrew, and David.

