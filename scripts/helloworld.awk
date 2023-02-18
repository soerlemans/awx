#!/usr/bin/awk -f
pattern1 { action; } # just like lex
pattern2 { action; }
BEGIN {
	if (1) {
		print "monkey yes"
	}else{
		print "monkey no"
	}

}
