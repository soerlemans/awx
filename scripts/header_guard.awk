#!/usr/bin/env -S awk -f 


BEGIN {
}

/^#(define)|(ifndef)|(endif).+_HPP$/ {
	print $0
}
