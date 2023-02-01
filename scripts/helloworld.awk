#!/usr/bin/awk -f


function helloworld(t_name)
{
	print "I like ", t_name, "!"
}

BEGIN {
	"test" "test2"
}


BEGIN {

	# This is causes a terminator expected error!
	# a = b + c;

	helloworld("monkeys")
}
