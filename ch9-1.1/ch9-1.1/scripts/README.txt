============================================================================
ch9/scripts/README.txt
============================================================================

9th DIMACS Implementation Challenge: Shortest Paths
http://www.dis.uniroma1.it/~challenge9

Last changed:   $Date: 2006/02/17 12:05:29 $
Changed by:     $Author: demetres $
Revision:       $Revision: 1.4 $
============================================================================

This directory contains Perl scripts for generating synthetic and real-world 
core families and for running core experiments. Core families are created in 
ch9/inputs. Performance result files are created in ch9/results.

The Makefile includes commands to generate all core families and run all
core experiments. 

To build the core families and run the experiments, type 'make'. To create 
the families only, type 'make gen'. To run the experiments only, type 
'make run'.

Real-world core families are generated in the ch9/inputs directory by 
downloading them directly from the Challenge website, so you must be 
connected to the Internet when running 'make' or 'make gen'.

You may want to generate core families or run experiments individually. 
For instance, to generate the Random4-n family only, type 
'perl genRandom4-n.pl'. To generate only the graphs in the family, type: 
'perl genRandom4-n.gr.pl'. To run the core experiments on the Random4-n 
family only, type 'perl runRandom4-n.pl'. To run the ss experiment only,
type 'perl runRandom4-n.ss.pl'.

Perl script filename syntax:

[ "run" | "gen" ] + family-name + [ [ ".loc" | ".rnd" ] + ".p2p" | ".ss" | ".gr" ] + ".pl"

Current core family names are:

- Random4-n
- Random4-C
- Long-n
- Long-C
- Square-n
- Square-C
- USA-road-d
- USA-road-t

--------------------------------------------------------------------------
Note:

For the sake of reproducibility, we include the script file cutUSA-road.pl 
that we used to generate the USA-road-d and USA-road-t graph families, 
which are downloaded from the Challenge website by scripts genUSA-road-d and
genUSA-road-t. The script cutUSA-road.pl assumes that the TIGER/Line file 
USA.tmp appears as ch9/inputs/USA.tmp. The file USA.tmp has been obtained 
by stitching together the individual USA TIGER/Line files available at the 
Challenge website by using the program ch9/utils/merger/merger.exe.

To generate each USA-road-d and USA-road-t graph, cutUSA-road.pl performs  
the following steps:

- cuts the USA.tmp file along a specified bounding box
- converts the resulting TIGER file to list of edges in binary format 
  (reason: binary files are smaller and faster to handle)
- computes the connected components of the graph given in binary format
  (reason: cutting the USA.tmp graph may yield a disconnected subgraph)
- finds the vertices in the largest connected component of the graph
- extracts the TIGER subgraph induced by vertices of the largest cc
- renumbers node IDs in the resulting  TIGER file so that they are
  consecutive numbers in [0..n-1]
- converts the renumbered TIGER file to USA-road-d '.co' and '.gr' files
  using arc cost = distance (node IDs are in [1..n] in the .gr file)
- converts the renumbered TIGER file to USA-road-t '.co' and '.gr' files 
  using arc cost = travel time (node IDs are in [1..n] in the .gr file)

