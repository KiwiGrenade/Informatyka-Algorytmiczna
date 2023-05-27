------------------------------------------------------------
* 9th DIMACS Implementation Challenge: Shortest Paths
* http://www.dis.uniroma1.it/~challenge9
------------------------------------------------------------

This directory contains utility programs useful for 
converting and manipulating test instances for the 9th DIMACS 
implementation Challenge

-------------------------------------------------------------
FILE DESCRIPTION

  - tiger2edimacs.pl:
  
    the program converts TIGER/Line road graphs available at 
    the Challenge website to the extended DIMACS graph format

    usage: > perl tiger2edimacs.pl file1 file2 ...

    input:  file1, file2, etc. are files in TIGER/Line text 
            format (please find the format description at:
            http://www.dis.uniroma1.it/~challenge9/data/tiger)

    output: the program creates files as follows:

        - file1.gr: file1 converted to extended DIMACS format
        - file1.co: auxiliary file with node coords for file1
        - file2.gr: file2 converted to extended DIMACS format
        - file2.co: auxiliary file with node coords for file2
        - ...

  - cutter/cutter.exe:
  
    the program trims a USA TIGER/Line road graph using a
    given bounding box. Please see the related README file.

  - cutter/renumber.exe:
  
    the program renumbers node IDs of a USA TIGER/Line road 
    graph so that they are in the range [1,..,n], where n is 
    the number of nodes of the graph.

  - merger/merger.exe:
  
    the program merges one or more USA TIGER/Line road graph
    files into one file. Please see the related README file.
------------------------------------------------------------

