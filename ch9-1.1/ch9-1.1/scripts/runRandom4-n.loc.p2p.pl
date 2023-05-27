# ============================================================================
#  runRandom4-n.loc.p2p.pl
# ============================================================================

#  Author(s)       (c) 2005 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 20, 2005

#  Last changed:   $Date: 2005/11/27 15:03:27 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.2 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Random4-n family experiment driver
#  runs the p2p solver on local instances in the Random4-n family

#  Usage: > perl runRandom4-n.loc.p2p.pl
# ============================================================================

# param setup:
$NEXP    = 21;      # number of vertices = 2^$NEXP
$TRIALS  = 1;       # number of trials per data point

$RESFILE   = "../results/Random4-n.loc.p2p.res";
$PREFIX    = "../inputs/Random4-n/Random4-n";
$SOLVER    = "../solvers/mlb-dimacs/mbp.exe";
$GRAPH     = "$PREFIX.%s.%s.gr";
$AUX       = "$PREFIX.%s.%s.%s.p2p";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Random4-n family local p2p core experiment\n";

# open result file
open FILE, ">$RESFILE" or die "Cannot open $RESFILE for write :$!";

# run experiments for different degrees of locality of queries
for ( $baserank = 0; $baserank < 64; ++$baserank) {

	# run trials per data point
	for ( $trial = 0; $trial < $TRIALS; ++$trial) {

		$graphname = sprintf $GRAPH, $NEXP, $trial;
		$auxname   = sprintf $AUX, $NEXP, $trial, $baserank;

		# if aux file with given rank exists, run experiment and collect stdout
		if (-e $auxname) {
			$out = `$SOLVER $graphname $auxname`;
			chop($out);
			$out = sprintf "$out %4s\n", $baserank;
			print FILE $out;				
		}
	}
}

close FILE;


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
# License aRandom4 with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# ============================================================================

