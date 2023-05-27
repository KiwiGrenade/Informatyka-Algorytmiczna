# ============================================================================
#  Makefile
# ============================================================================

#  Author:         (c) 2005-2006 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        November 15, 2005
 
#  Last changed:   $Date: 2006/02/21 21:45:33 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.6 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Usage: > make         (Compiles generators, solvers, etc.)

#  Usage: > make gen     (Generates in ./inputs all core input families)
#  Usage: > make run     (Generates in ./results performace reports of benchmark  
#                         solvers on all core input families)

#  Usage: > make gen_gr  (Generates in ./inputs all gr input instances)

#  Usage: > make gen_ss  (Generates in ./inputs all ss input instances)
#  Usage: > make run_ss  (Generates in ./results performace reports of benchmark  
#                         solvers on ss core instances)

#  Usage: > make gen_p2p (Generates in ./inputs all p2p input instances)
#  Usage: > make run_p2p (Generates in ./results performace reports of benchmark  
#                         solvers on p2p core instances)

#  Usage: > make clean   (Cleans up the package)

all: code

code:
	cd ./gens;    $(MAKE)
	cd ./solvers; $(MAKE)
	cd ./utils;   $(MAKE)

gen:
	cd ./scripts; $(MAKE) -i

run:
	cd ./scripts; $(MAKE) -i run

gen_gr:
	cd ./scripts; $(MAKE) -i gen_gr

gen_ss:
	cd ./scripts; $(MAKE) -i gen_ss

run_ss:
	cd ./scripts; $(MAKE) -i run_ss

gen_p2p:
	cd ./scripts; $(MAKE) -i gen_p2p

run_p2p:
	cd ./scripts; $(MAKE) -i run_p2p

clean:
	cd ./gens;    $(MAKE) clean
	cd ./solvers; $(MAKE) clean
	cd ./utils;   $(MAKE) clean
	cd ./scripts; $(MAKE) clean


#  Copyright (C) 2005-2006 Camil Demetrescu, Andrew Goldberg

#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA 
