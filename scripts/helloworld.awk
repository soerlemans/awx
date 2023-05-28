#!/usr/bin/env -S awk -f


BEGIN {
	i = 0 == 5
	print i
}


/BEGIN/ {
	print "Found BEGIN!"
}

1 && 1 {
	print "Found BEGIN!"
}
