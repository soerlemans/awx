#!/usr/bin/awk -f


function helloworld(t_name)
{
	print "I like ", t_name, "!"
}

BEGIN {
	helloworld("monkeys")
}
