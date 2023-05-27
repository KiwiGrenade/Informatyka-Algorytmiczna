# ============================================================================
#  cutUSA-road.pl
# ============================================================================

#  Author(s)       (c) 2005 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 25, 2005

#  Last changed:   $Date: 2006/10/30 08:09:39 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.9 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  USA-road-d and USA-road-t graph family generator (obtained by cutting 
#  the TIGER/Line USA graph)

#  The program assumes that the pathname of the TIGER/Line USA.tmp file
#  is ch9/inputs/USA.tmp

#  Usage: > perl cutUSA-road.pl
# ============================================================================

# param setup:

$SOURCE  = "../inputs/USA.tmp";
$CUTTER  = "../utils/cutter/cutter.exe";
$T2BIN   = "../utils/maxcc/tiger2bin.exe";
$UCON    = "../utils/maxcc/cc.exe";
$LACC    = "../utils/maxcc/largestcc.exe";
$SUBG    = "../utils/maxcc/subgraph.exe";
$RENUM   = "../utils/cutter/renumber.exe";
$TRANS   = "../utils/tiger2edimacs.pl";
$DIR     = "../inputs/USA-road-d";
$DIRT    = "../inputs/USA-road-t";
$PREFIX  = "$DIR/USA-road-d";
$PREFIXT = "$DIRT/USA-road-t";

$MEMCUTSIZE = 100;
$CCMSIZE    = 10000;
$LCCMSIZE   = 1000000;
$SGMSIZE    = 100;
$MEMSIZE    = 600;

$CUT = 1;     # if 0 then the cutting procedure is disabled
$T2B = 1;     # if 0 then the conversion to binary format is disabled
$UCC = 1;     # if 0 then the computation of connected comp. is disabled
$LCC = 1;     # if 0 then the computation of the largest cc is disabled
$SGR = 1;     # if 0 then the extraction of the induced cc subgraph is disabled
$REN = 1;     # if 0 then the renumbering procedure is disabled
$TRA = 1;     # if 0 then the TIGER->edimacs-d conversion is disabled
$TRT = 1;     # if 0 then the TIGER->edimacs-t conversion is disabled

# creates output directories (if they do not exist)
system "mkdir -p $DIR";
system "mkdir -p $DIRT";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* USA-road-d + USA-road-t family graph generator\n";

#conversion subroutine
sub DOCONV {
    $EXT = $_[0];
    $X1  = $_[1];
    $Y1  = $_[2];
    $X2  = $_[3];
    $Y2  = $_[4];

    # cut USA.tmp file along the given bounding box
    if ($CUT) { system "$CUTTER $MEMCUTSIZE $SOURCE $PREFIX.$EXT.org $X1 $Y1 $X2 $Y2"; }

    # convert tiger file to list of edges in binary format 
    if ($T2B) { system "$T2BIN $PREFIX.$EXT.org $PREFIX.$EXT.bin"; }

    # cutting the USA.tmp graph may yield a disconnected subgraph, therefore
    # compute connected components of the graph given in binary format
    if ($UCC) { system "$UCON $CCMSIZE $PREFIX.$EXT.bin $PREFIX.$EXT.cc"; }

    # find the vertices in the largest connected component of the graph
    if ($LCC) { system "$LACC $LCCMSIZE $PREFIX.$EXT.cc $PREFIX.$EXT.lcc"; }

    # extract subgraph induced by vertices of the largest cc
    if ($SGR) { system "$SUBG $SGMSIZE $PREFIX.$EXT.lcc $PREFIX.$EXT.org $PREFIX.$EXT"; }

    # renumber node IDs so that they are consecutive in [1..n]
    if ($REN) { system "$RENUM $MEMSIZE $PREFIX.$EXT"; }

    # convert tiger file to edimacs format (arc cost = distance x 100)
    if ($TRA) { system "perl $TRANS $PREFIX.$EXT"; }

    # convert tiger file to edimacs format (arc cost = travel time x 100)
    if ($TRT) { system "mv $PREFIX.$EXT $PREFIXT.$EXT";
                system "perl $TRANS -T $PREFIXT.$EXT"; 
                system "mv $PREFIXT.$EXT $PREFIX.$EXT"; }
}


# NY: 40.3-41.3 lat-N / 73.5-74.5 lon-W
&DOCONV("NY", -74500000, 41300000, -73500000, 40300000);

# BAY: 37.0-39.0 lat-N / 121-123 lon-W
&DOCONV("BAY", -123000000, 39000000, -121000000, 37000000);

# COL: 37.0-41.0 lat-N / 102-109 lon-W
&DOCONV("COL", -109000000, 41000000, -102000000, 37000000);

# FLA: 24.0-31.0 lat-N / 79-87.5 lon-W
&DOCONV("FLA", -87500000, 31000000, -79000000, 24000000);

# NW:  42.0-50.0 lat-N / 116-126 lon-W
&DOCONV("NW", -126000000, 50000000, -116000000, 42000000);

# NE:  39.5-43.0 lat-N / 64-76 lon-W
&DOCONV("NE", -76000000, 43000000, -64000000, 39500000);

# CAL: 32.5-42.0 lat-N / 114-125 lon-W
&DOCONV("CAL", -125000000, 42000000, -114000000, 32500000);

# LKS: 41.0-50.0 lat-N / 74-93 lon-W
&DOCONV("LKS", -93000000, 50000000, -74000000, 41000000);

# E:   24.0-50.0 lat-N / 64-79 lon-W
&DOCONV("E", -79000000, 50000000, -64000000, 24000000);

# W:   27.0-50.0 lat-N / 100-130 lon-W
&DOCONV("W", -130000000, 50000000, -100000000, 27000000);

# CTR: 25.0-50.0 lat-N / 79-100 long-W
&DOCONV("CTR", -100000000, 50000000, -79000000, 25000000);

# USA:
#if ($CUT) { $CUT = 0; system "cp $SOURCE $PREFIX.USA.org"; }
&DOCONV("USA", 0, 0, 0, 0);

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

