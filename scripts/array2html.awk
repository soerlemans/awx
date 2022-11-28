#!/usr/bin/gawk -f
# ___  _  _ ____ ___ ___ ____ ___  ____ 
# |  \ |  | |     |   |  |__| |__] |___ 
# |__/ |__| |___  |   |  |  | |    |___ 
#
# The scripts were written to be usefull in
# a research enviornment, but anyone is welcome
# to use them.  Happy awking.  -Tim Sherwood

BEGIN {
	FS =":";
	printf  "%s%s%s", 
		"<TABLE cellpadding=\"1pt\" BORDER=\"2pt\" ",
		"CELLSPACING=\"0pt\" bgcolor=\"\#ffffff\" ",
		"bordercolor=\"\#000000\">\n";

}

(NR==1){
	printf "   <TR bgcolor=\"\#dfdfdf\">\n"
	for( i=1; i<=NF; i++ )
	{
		printf "      <TD><center>%s</center></TD>\n", $i;
	}
	printf "   </TR>\n"
}

(NF>0 && NR>1){

	printf "   <TR>\n"
	for( i=1; i<=NF; i++ )
	{
		if ( i==1 ) {
			printf "      <TD align=left>%s</TD>\n", $i;
		} else {
			printf "      <TD align=right>%s</TD>\n", $i;
		}
	}
	printf "   </TR>\n"
}

END {
	printf "</TABLE>\n";
	i = 0.2;
	i = 0x299;
	i = 0x99.99;
}
