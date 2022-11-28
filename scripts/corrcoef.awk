#!/usr/bin/gawk -f 
# ___  _  _ ____ ___ ___ ____ ___  ____ 
# |  \ |  | |     |   |  |__| |__] |___ 
# |__/ |__| |___  |   |  |  | |    |___ 
#
# The scripts were written to be usefull in
# a research enviornment, but anyone is welcome
# to use them.  Happy awking.  -Tim Sherwood

BEGIN {
	FS = ":";
}

{
	xy+=($1*$2); 
	x+=$1; 
	y+=$2; 
	x2+=($1*$1); 
	y2+=($2*$2);
} 

END { 
	print "NR=" NR; 
	ssx=x2-((x*x)/NR); 
	print "ssx=" ssx; 
	ssy=y2-((y*y)/NR); 
	print "ssy=" ssy; 
	ssxy = xy - ((x*y)/NR); 
	print "ssxy=" ssxy; 
	r=ssxy/sqrt(ssx*ssy); 
	print "r=" r; 
}
