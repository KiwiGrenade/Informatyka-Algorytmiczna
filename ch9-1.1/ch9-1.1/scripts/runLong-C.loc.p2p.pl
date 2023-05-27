# ============================================================================
#  runLong-C.loc.p2p.pl
# ============================================================================

#  Author(s)       (c) 2005 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 20, 2005

#  Last changed:   $Date: 2006/03/20 17:39:26 $
#  Changed by:     $Author: goldberg $
#  Revision:       $Revision: 1.2 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Long-C family experiment driver
#  runs the p2p solver on local instances in the Long-C family

#  Usage: > perl runLong-C.loc.p2p.pl
# ============================================================================

# param setup:
$START   = 0;       # max arc weight C goes from 4^$START to 4^$END
$END     = 15;
$TRIALS  = 1;       # number of trials per data point

$RESFILE   = "../results/Long-C.loc.p2p.res";
$PREFIX    = "../inputs/Long-C/Long-C";
$SOLVER    = "../solvers/mlb-dimacs/mbp.exe";
$GRAPH     = "$PREFIX.%s.%s.gr";
$AUX       = "$PREFIX.%s.%s.%s.p2p";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Long-C family local p2p core experiment\n";


# delete result file
unlink($RESFILE);

# generation loop:
for ( $p = $START; $p < $END + 1 ; $p++ ) { 

    # run experiments for different degrees of locality of queries
    for ( $baserank = 0; $baserank < 64; ++$baserank) {

		# run trials per data point
		for ( $trial = 0; $trial < $TRIALS; ++$trial) {

			$graphname = sprintf $GRAPH, $p, $trial;
			$auxname   = sprintf $AUX, $p, $trial, $baserank;

			# if aux file with given rank exists, run experiment and collect stdout
			if (-e $auxname) {
				`$SOLVER $graphname $auxname $RESFILE;`
			}
		}
	}
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
# License aSquare with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# ============================================================================

