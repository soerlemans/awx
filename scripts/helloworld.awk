#!/usr/bin/env -S awk -f

# Need to fix left associativity for this to work
# NR <= 2 && /^#(define|ifndef).+_HPP$/ {
# 		i = NR >= 2
# 		print $0, NR
# }

{
	print 30 - 20
}
