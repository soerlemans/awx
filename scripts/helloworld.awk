#!/usr/bin/env -S awk -f


{
	print match($0, "match")
}

