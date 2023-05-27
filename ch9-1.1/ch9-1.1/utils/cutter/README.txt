------------------------------------------------------------
* 9th DIMACS Implementation Challenge: Shortest Paths
* http://www.dis.uniroma1.it/~challenge9
------------------------------------------------------------

This directory contains utility programs useful for 
converting and manipulating test instances for the 9th DIMACS 
implementation Challenge

-------------------------------------------------------------
FILE DESCRIPTION

  - cutter.exe:
  
    the program trims a USA TIGER/Line road graph along a
    given bounding box. The output graph is a subgraph induced by
    all nodes whose coordinates fall in the bounding box.
    Since node IDs remain the same, one may need to renumber them
    so that they are consecutive numbers in [1,n], where n is the
    number of nodes of the graph.

    To compile the program, type 'make'.

    usage: > ./cutter.exe memsize (in MBytes) inFile outFile x1 y1 x2 y2

    input:  memsize = estimated free main memory available 
                      (the larger, the faster the program)
            inFile  = pathname of the TIGER/Line to be cut
            outFile = pathname of the output TIGER/Line file
            x1, y1  = coord of the left-top corner of the 
                      bounding box (see below)
            x2, y2  = coord of the right-bottom corner of the 
                      bounding box (see below) 

                      (x1, y1) -> +------------+
                                  |            |
                                  |            |
                                  +------------+ <- (x2, y2)
                     
                      Please find coordinate description at: 
                      http://www.dis.uniroma1.it/~challenge9/data/tiger

    output: the program creates one TIGER/Line file.

    IMPORTANT NOTE: if the resulting graph has n nodes, 
    node IDs may not be consecutive numbers in [0..n-1].
    To renumber node IDs, please use renumber.exe.

  - renumber.exe:
  
    the program renumbers node IDs of a USA TIGER/Line road 
    graph so that they are in the range [0,..,n-1], where n is 
    the number of nodes of the graph.

    To compile the program, type 'make'.

    usage: > ./renumber.exe memsize (in MBytes) inFileName

    input:  memsize     = estimated free main memory available 
                          (the larger, the faster the program)
            inFileName  = pathname of the TIGER/Line to be 
                          renumbered

    output: the program overwrites the input TIGER/Line file.

------------------------------------------------------------

