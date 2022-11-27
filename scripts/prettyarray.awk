#!/usr/bin/gawk -f 
# ___  _  _ ____ ___ ___ ____ ___  ____ 
# |  \ |  | |     |   |  |__| |__] |___ 
# |__/ |__| |___  |   |  |  | |    |___ 
#
# The scripts were written to be usefull in
# a research enviornment, but anyone is welcome
# to use them.  Happy awking.  -Tim Sherwood


#this is really darn handy but a little messy to read
#if you have a rewrite of this that does the same time of
#stuff, please let me know

BEGIN {
	FS = ":";
	if ( NOSEP ) {
		vertsep = "";	
		horzsep = "";	
		cornersep = "";
	} else {
		vertsep = "|";	
		horzsep = "-";	
		cornersep = "+";
	}
}


{
	if (NF>n) n=NF;
	for (i=1; i<=NF; i++) 
	{
		d[i,NR] = $i;
		if(m[i]<length($i))
		{
			m[i]=length($i);
		}
	}
}

END {
	for( i=1; i<=n; i++ ) 
	{
		for ( j=1; j<=m[i]+3; j++ ) 
		{
			if ((i!=1) || (j!=1)) {
				div = sprintf("%s%c",div,horzsep );
			}
		}

		if ( i!= n ) {
			div = sprintf("%s%c",div, cornersep);
		}
	}
	if ( length(horzsep) == 0 && length(cornersep) == 0 ) nodiv=1;
	for( r=1; r<=NR; r++ ) 
	{
		if ( d[1,r]!=last && nodiv==0) {
			printf "%s\n", div;
		}
		last = d[1,r];
		for( i=1; i<n; i++ ) 
		{
			f = sprintf("%%%ds %%s ",m[i]+1);
			printf f, d[i,r], vertsep;
		}
		f = sprintf("%%%ds\n",m[n]+1);
		printf f, d[n,r];
	}
}

