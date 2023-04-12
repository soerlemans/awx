#!/usr/bin/env -S awk -f
BEGIN {
		if(100 == "1000")
				print "true"
		else
				print "false"
}

