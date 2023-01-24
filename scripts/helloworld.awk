#!/usr/bin/awk -f
BEGIN {
	+10 - 20.2

	getline var

	var += 0xFF;

	print "Hello World!"
}
