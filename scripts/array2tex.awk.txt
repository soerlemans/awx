#!/usr/bin/gawk -f
# ___  _  _ ____ ___ ___ ____ ___  ____ 
# |  \ |  | |     |   |  |__| |__] |___ 
# |__/ |__| |___  |   |  |  | |    |___ 
#
# The scripts were written to be usefull in
# a research enviornment, but anyone is welcome
# to use them.  Happy awking.  -Tim Sherwood

#print the begin stuff
BEGIN{
	FS =":";

	if ( FORPRINT ) {
		print "\\documentstyle{article}";
		print "\\textheight 9.00in";
		print "\\columnsep 2.0pc";   
		print "\\textwidth 7in";
		print "\\headheight 0.0in"; 
		print "\\headsep 0.0in";
		print "\\oddsidemargin -.20in";  
		print "\\footheight 0.0in";
		print "\\topmargin -.25in";
		print "\\begin{document}";
		printf "\\scriptsize\n";
		printf "\\begin{center}\n";
	} else {
		printf "\\small\n";
		printf "\\begin{center}\n";
	}
}

#print the header info
(NR==1 && NF>=1){
	printf "\\begin{tabular}{|"
	printf "l|";
	for(i=2;i<=NF;i++) {
		printf "r|";
	}
	printf "}\n";
	printf "\\hline\n";

	for(i=1;i<=NF;i++) {
		printf "\\multicolumn{1}{|c|}{%s}",$i;
		if (i!=NF) printf " &";
		printf "\n";
	}

	printf "\\\\\\hline\\hline\n";
}

#print the data
(NR!=1 && NF>=1){
	printf "%s ", $1;
	for(i=2;i<=NF;i++) {
		printf "& %s ", $i;
	}
	printf "\\\\\\hline\n";
}

#print the trailer info
END {
	#printf "\\hline\n";
	printf "\\end{tabular}\n";
	printf "\\end{center}\n";
	if ( FORPRINT ) {
		printf "\\end{center}\n";
	}
}
