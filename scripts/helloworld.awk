#!/usr/bin/env -S awk -f


{
	print index($0, "45")
}

