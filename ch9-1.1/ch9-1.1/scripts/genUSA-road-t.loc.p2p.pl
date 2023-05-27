# ============================================================================
#  genUSA-road-t.loc.p2p.pl
# ============================================================================

#  Author(s)       (c) 2006 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Feb 15, 2006

#  Last changed:   $Date: 2006/02/21 16:47:46 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.2 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Local point-to-point query generator for the USA-road-t family
#  Creates a suite of point-to-point shortest path
#  problem-specific auxiliary files.

#  Usage: > perl genUSA-road-t.loc.p2p.pl
# ============================================================================

# param setup:

$NUMSRC   = 100;     # num local query sources
$BASERANK = 9;       # log of initial Dijkstra rank for destination in query pair
$SEED     = 971;     # seed of pseudo-random generator

$GENPATH  = "../gens/local_q/mb.exe";
$DIR      = "../inputs/USA-road-t";
$FORMAT   = "$DIR/USA-road-t.%s";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Random query generator for the USA-road-t family\n";

# creates directory (if does not exist)
system "mkdir -p $DIR";

# generation routine
sub DOGEN { 

    # graph instance (e.g., CTR, BAY, etc.)
    $EXT = $_[0]; 

	$graphprefix = sprintf $FORMAT, $EXT;
    print "\n>> Generating local p2p instances for graph $graphprefix\n";

    printf "   - Generating file(s) %s.X.p2p [seed %-10s] ...", $graphprefix, $SEED;

    # call query generator
    system "$GENPATH $graphprefix $NUMSRC $BASERANK $SEED";
}

# generate local p2p instances
#&DOGEN("NY");
#&DOGEN("BAY");
#&DOGEN("COL");
#&DOGEN("FLA");
#&DOGEN("NW");
#&DOGEN("NE");
#&DOGEN("CAL");
&DOGEN("LKS");
#&DOGEN("E");
#&DOGEN("W");
#&DOGEN("CTR");


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

