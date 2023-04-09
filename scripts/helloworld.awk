#!/usr/bin/env -S awk -f


function test(t_arg, owww, yeahhh)
{
	print t_arg, owww, yeahhh
}

BEGIN {
	test(120, 200, 100)
}
