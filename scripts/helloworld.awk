#!/usr/bin/env -S awk -f

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

#	print (10, 20) in var

	print "10" * "10"
	print -"10"
	print -"fff"

	print toupper("hello world")
	system("ls")

	print $0
}
