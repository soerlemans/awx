#!/usr/bin/env -S awk -f


BEGIN {
		getline var

		print "var:", var
		print "var + var:", var + var
}

