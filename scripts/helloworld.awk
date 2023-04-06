#!/usr/bin/env -S awk -f


function test (t_arg, owww, yeahhh) {
		print t_arg, owww, yeahhh
}

function noreturn(){
		addition = 20
}

BEGIN {
		test(100, 200, 100)

		print 100, 200, 100
		print t_arg, owww, yeahhh
}

