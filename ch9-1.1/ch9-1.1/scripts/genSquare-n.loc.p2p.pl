# ============================================================================
#  genSquare-n.loc.p2p.pl
# ============================================================================

#  Author(s)       (c) 2005 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 9, 2005

#  Last changed:   $Date: 2005/11/27 09:08:45 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.3 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Random point-to-point query generator for the Square-n family
#  Creates a suite of point-to-point shortest path
#  problem-specific auxiliary files.

#  Usage: > perl genSquare-n.loc.p2p.pl
# ============================================================================

# param setup:

$NUMSRC   = 100;     # num random query sources
$BASERANK = 9;       # log of initial Dijkstra rank for destination in query pair
$NEXP     = 21;      # number of nodes
$SEED     = 971;     # seed of pseudo-random generator
$TRIALS   = 1;       # number of trials per data point

$GENPATH  = "../gens/local_q/mb.exe";
$DIR     = "../inputs/Square-n";
$FORMAT   = "$DIR/Square-n.%s.%s";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Random query generator for the Square-n family\n";

# creates directory (if does not exist)
system "mkdir -p $DIR";

#init seed
srand ($SEED);

# compute actual number of nodes 
# (for odd values of p $n won't be a power of 2)
$idealn = (1<<$NEXP);
$height = int(sqrt($idealn));
$width  = int($idealn / $height);
$n = $height * $width;

$str = $NEXP % 2 ? "n=$n < $idealn=2^$NEXP" : "n=$n=2^$NEXP";
print "\n>> Generating local p2p instances for data point [$str]\n";

# generate trials per data point
for ( $trial = 0; $trial < $TRIALS; ++$trial) {

	$graphprefix = sprintf $FORMAT, $NEXP, $trial;
	$trialseed = int(rand(0x7FFFFFFF));
	printf "   - Generating file(s) %s.X.p2p [seed %-10s] ...", $graphprefix, $trialseed;

	# call query generator
	system "$GENPATH $graphprefix $NUMSRC $BASERANK $trialseed";
}


# ============================================================================
# Copyright (C) 2005 Camil Demetrescu, Andrew Goldberg

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

