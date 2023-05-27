============================================================================
ch9/inputs/README.txt
============================================================================

9th DIMACS Implementation Challenge: Shortest Paths
http://www.dis.uniroma1.it/~challenge9

Last changed:   $Date: 2006/02/17 12:05:29 $
Changed by:     $Author: demetres $
Revision:       $Revision: 1.3 $
============================================================================

This directory is intended to contain input test sets for shortest path
solvers. Core test sets are put here by scripts in ch9/scripts/.

File name conventions:

- graph file: 
      family-name.param[.trial].gr

- single-source aux file:
      family-name.param[.trial].ss

- random p2p query pairs file:
      family-name.param[.trial].p2p

- local p2p query pairs file:
      family-name.param[.trial].base-rank.p2p

Where:

family-name = the name of the input family (e.g, Long-n, Square-C, etc.)

param = number of nodes in [2^10, 2^21] (for -n families)
        log_4 of max arc weight (for -C families)
        graph name (for USA-road families)

trial = optional instance number, in case more than one input instance for 
        the same data point is generated (in this version = 0, but you may 
        want to increase it by editing the gen and run scripts)

base-rank = for local p2p queries of the form (x,y), the base rank is approx 
            the log_2 of the Dijkstra rank of y with source x. The smaller the
            rank, the more local is the query.

