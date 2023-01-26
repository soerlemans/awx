#!/usr/bin/awk -f
BEGIN {
	getline var

	# var && var;
	var += 10;
	var += 0xFF;

	# Parser fails after returning of array subscript
	# Nullptr being returned somehwere?
	# var[name]


	print "Hello World!"
}
