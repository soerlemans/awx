#!/usr/bin/gawk -f
# ___  _  _ ____ ___ ___ ____ ___  ____ 
# |  \ |  | |     |   |  |__| |__] |___ 
# |__/ |__| |___  |   |  |  | |    |___ 
#
# The scripts were written to be usefull in
# a research enviornment, but anyone is welcome
# to use them.  Happy awking.  -Tim Sherwood

func get01string(innum,       t, retstr, i) {

        retstr = "";
        t=innum;
	while( t )
        {
                if ( t%2==0 ) {
                        retstr = "0" retstr;
                } else {
                        retstr = "1" retstr;
                }
                t = int(t/2);
        }

        return retstr;
}


{
	print	get01string( $1 );
}
