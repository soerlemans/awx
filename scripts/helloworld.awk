#!/usr/bin/awk -f


function helloworld(t_name)
{
	print "I like ", t_name, "!"
}

BEGIN {
	# "test" "test2"
}


BEGIN {
	# print (count == 0) ? "Starting with count of 0" : "Huh?";
	# count == 0

	helloworld("monkeys")

	if(1){
		print "monkey yes"
	}else{
		print "monkey no"
	}
}
