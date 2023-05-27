# ============================================================================
#  tiger2edimacs.pl
# ============================================================================

#  Author(s)       (c) 2005 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 9, 2005

#  Last changed:   $Date: 2006/10/30 08:09:39 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.5 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  converts TIGER/Line files available at the Challenge website
#  into the extended DIMACS format

#  Usage: > perl tiger2edimacs.pl [-T] filename1 filename2 ...
# ============================================================================

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* TIGER/Line to Challenge 9 graph format converter\n";

# arc cost is distance by default
$arccost = 1;

# for each command line arg
foreach (@ARGV) {

    # if parameter is -T then arc cost is travel time
    if ($_ eq '-T') { $arccost = 0; next; }

    # pick filename
    $infilename = $_;
    
    # cut path and keep just the file name
    @details = split /\//, $infilename;
    $justthename = $details[scalar(@details)-1];

    # build output file names
    $grfilename = $infilename.".gr";
    $cofilename = $infilename.".co";

    print "\n>> Converting $infilename ...";

    # open input file
    open INFILE, $infilename or die "Cannot open $infilename for read :$!";

    # read number of nodes
    chop($n = <INFILE>);

    # skip node description
    for ($i = 0; $i < $n; ++$i) {
        $line = <INFILE>;
    }

    # read number of edges
    chop($m = <INFILE>);
    $mm = 2*$m;

    # close input file
    close INFILE;

    # re-open input file
    open INFILE, $infilename or die "Cannot open $infilename for read :$!";

    # open output graph file
    open GRFILE, ">$grfilename" or die "Cannot open $grfilename for write :$!";

    # open output coordinate file
    open COFILE, ">$cofilename" or die "Cannot open $grfilename for write :$!";

    # write gr header
    print GRFILE "c 9th DIMACS Implementation Challenge: Shortest Paths\n";
    print GRFILE "c http://www.dis.uniroma1.it/~challenge9\n";
    print GRFILE "c TIGER/Line graph $justthename\n";
    print GRFILE "c\n";
    print GRFILE "p sp $n $mm\n";
    print GRFILE "c graph contains $n nodes and $mm arcs\n";
    print GRFILE "c\n";

    # write co header
    print COFILE "c 9th DIMACS Implementation Challenge: Shortest Paths\n";
    print COFILE "c http://www.dis.uniroma1.it/~challenge9\n";
    print COFILE "c TIGER/Line nodes coords for graph $justthename\n";
    print COFILE "c\n";
    print COFILE "p aux sp co $n\n";
    print COFILE "c graph contains $n nodes\n";
    print COFILE "c\n";

    # skip node count line
    $line = <INFILE>;

    # scan nodes
    for ($i = 0; $i < $n; ++$i) {
        $line = <INFILE>;
        ($id, $xcoord, $ycoord) = split /\s/, $line;
        $id++; # extended DIMACS node IDs go from 1 to n
        print COFILE "v $id $xcoord $ycoord\n";
    }

    # close coord file
    close COFILE;

    # skip arc count line
    $line = <INFILE>;

    # scan arcs
    for ($i = 0; $i < $m; ++$i) {

        # read edge pairs
        $line = <INFILE>;
        ($src, $target) = split /\s/, $line;

        # read edge attributes
        $line = <INFILE>;
        ($traveltime, $length, $category) = split /\s/, $line;

        # adjust parameters
        $src ++;                    # extended DIMACS node IDs go from 1 to n
        $target ++;                 # extended DIMACS node IDs go from 1 to n

        if ($arccost) {
            $intcost = int(10 * $length + .5);      # extended DIMACS arc weights must be integral
        }
        else {
            $intcost = int(10 * $traveltime + .5);  # extended DIMACS arc weights must be integral
        }

        # write arc to output graph file
        print GRFILE "a $src $target $intcost\n";
        print GRFILE "a $target $src $intcost\n";
    }

    close INFILE;
    close GRFILE;

    print " [DONE]\n";
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

