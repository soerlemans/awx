#!/usr/bin/env -S awk -f

# Need to fix left associativity for this to work
# NR <= 2 && /^#(define|ifndef).+_HPP$/ {
# 		i = NR >= 2
# 		print $0, NR
# }

{
	print 20 - 30 * 20
	print 4 - 4 && 1
	print 2 - 2 || 1 - 1

	print var = 10
	print var * 2

	print +20 && -20

	print var++
	print var++
	print ++var

	new_var = 10 * 10 == 10
	print new_var

	print newvar var
}
