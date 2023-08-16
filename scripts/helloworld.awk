#!/usr/bin/env -S awk -f


{
		test = $0
		var = test ~ "match"
		print var, RSTART, RLENGTH
}

