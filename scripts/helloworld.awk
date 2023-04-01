#!/usr/bin/env -S awk -f


BEGIN {
	if (10.001 == "10.001") {
		print ("Wow")
	} else {
		print ("False")
	}

	if ("10.0019999" == 10.0019999) {
		print ("Wow")
	} else {
		print ("False")
	}
}

