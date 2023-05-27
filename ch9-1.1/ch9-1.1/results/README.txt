============================================================================
ch9/results/README.txt
============================================================================

9th DIMACS Implementation Challenge: Shortest Paths
http://www.dis.uniroma1.it/~challenge9

Last changed:   $Date: 2006/02/16 20:53:42 $
Changed by:     $Author: demetres $
Revision:       $Revision: 1.2 $
============================================================================

This directory is intended to contain performance report files for core
experiments. Reports are generated here by "run" scripts in ch9/scripts/.

File name conventions:

- single-source experiment result file:
      family-name.ss.res

- random p2p query experiment result file:
      family-name.rnd.p2p.res

- local p2p query pairs file:
      family-name.loc.p2p.res

File content: files contain performance reports, one per line. Each line
is a space-separated sequence of fields:

1. t, just a tag -- ignore it
2. n, the number of nodes of the graph
3. m, the number of arcs of the graph
4. minimum arc weight 
5. maximum arc weight 
6. average time per operation in milliseconds 
   (time per query for p2p, time per source processing in ss)
7. number of graph nodes visited by the solver

In the special case of loc.p2p files, there is an additional field:

8. log base 2 of the Dijkstra rank of each destination when executing Dijkstra
   from each source (this is a measure of query locality).

