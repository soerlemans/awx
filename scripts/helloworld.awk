#!/usr/bin/env -S awk -f


function test(t_arg, owww, yeahhh)
{
	yeahhh = 10
	print t_arg, owww, yeahhh
	print owww
	print yeahhh
}

function test2(t_arg3, owww3, yeahhh4)
{
	print t_arg3, owww3, yeahhh4
}

BEGIN {
	test(120, 200, 100)
	test2(101, 209, 300)
	print
	print 100, 200, 100
	print t_arg3, owww, yeahhh

	print 10, jfjf, fjfj
}
