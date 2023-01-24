#!/usr/bin/awk -f
BEGIN {
	getline var

	# var && var;
	var += 10;

	# var += 0xFF;

	print "Hello World!"
}
