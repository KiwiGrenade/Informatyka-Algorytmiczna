# ============================================================================
#  genUSA-road-t.rnd.p2p.pl
# ============================================================================

#  Author(s)       (c) 2006 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Feb 15, 2006

#  Last changed:   $Date: 2006/02/21 16:47:46 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.2 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Random point-to-point query generator for the USA-road-t family
#  Creates a suite of point-to-point shortest path
#  problem-specific auxiliary files.

#  Usage: > perl genUSA-road-t.rnd.p2p.pl
# ============================================================================

# param setup:

$NUMQUERY = 1000;    # num queries
$SEED     = 971;     # seed of pseudo-random generator

$DIR    = "../inputs/USA-road-t";
$GRAPHF = "$DIR/USA-road-t.%s.gr";
$FORMAT = "$DIR/USA-road-t.%s.p2p";


# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Random query generator for the USA-road-t family\n";


# creates directory (if does not exist)
system "mkdir -p $DIR";

# routine that extracts the number of nodes and edges from a .gr file
sub GET_GRAPH_NM {

    $param = $_[0]; 

    # open graph file
    open GRFILE, "$param" or die "Cannot open $param for read :$!";

    # get number of nodes and edges of the graph
    $found = 0;
    loop: while(<GRFILE>) {
        @line = split /\s/, $_;
        if ($line[0] eq "p") {
            $n = $line[2];
            $m = $line[3];
            $found = 1;
            last loop;
        }
    }

    close GRFILE;

    if ($found == 0) {
        print "Error: graph does not contain a problem line\n";
        exit;
    }
}

# generation loop:
sub DOGEN { 

    # graph instance (e.g., CTR, BAY, etc.)
    $EXT = $_[0]; 

    # format input graph name
    $grfile = sprintf $GRAPHF, $EXT;

    # get number of nodes and edges of the graph
    &GET_GRAPH_NM($grfile);

    print "\n>> Generating rnd p2p instances for graph $grfile [n=$n]\n";

    $pathname = sprintf $FORMAT, $EXT;

    printf "   - Generating file %s [seed %-10s] ...",$pathname, $SEED;

    # open file in write mode
    open FILE, ">$pathname" or die "Cannot open $pathname for write :$!";

    # write file header
    print FILE "c 9th DIMACS Implementation Challenge: Shortest Paths\n";
    print FILE "c http://www.dis.uniroma1.it/~challenge9\n";
    print FILE "c USA-road-t family p2p problem aux file\n";
    print FILE "c\n";
    print FILE "p aux sp p2p $NUMQUERY\n";
    print FILE "c graph contains $n nodes\n";
    print FILE "c file contains $NUMQUERY query pairs\n";
    print FILE "c\n";

    # write $NUMSRC random node pairs to the file
    for ( $i = 0; $i < $NUMQUERY; ++$i ) {
        $src  = 1 + int(rand($n));            
        $dest = 1 + int(rand($n));            
        print FILE "q $src $dest\n";
    }

    # close file
    close FILE;
   
    print " [DONE]\n";
}

# generate p2p instances
&DOGEN("NY");
&DOGEN("BAY");
&DOGEN("COL");
&DOGEN("FLA");
&DOGEN("NE");
&DOGEN("NW");
&DOGEN("CAL");
&DOGEN("LKS");
&DOGEN("E");
&DOGEN("W");
&DOGEN("CTR");


# ============================================================================
# Copyright (C) 2006 Camil Demetrescu, Andrew Goldberg

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# ============================================================================

