#!/usr/bin/env -S awk -f


BEGIN {
	if (10.001 == "10.001") {
		print ("Wow")
	} else {
		print ("False")
	}
}

