#!/usr/bin/env -S awk -f


function test () {
		# print "printing"

		return 10;
}

function noreturn(){
		addition = 20
}

BEGIN {
		print("Results:", test(), noreturn(), 30)
}

