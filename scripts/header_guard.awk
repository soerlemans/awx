#!/usr/bin/env -S gawk -i inplace -f

# This script is very useful to run with:
# shopt -s globstar
# Then you can use **.hpp

# Generate header guard
function gen()
{
	guard = toupper(FILENAME)
	gsub(/(\/)|(\.)/, "_", guard)
	gsub("SRC", "AWX", guard)

	return guard
}

# Replace header guard definition with unique header guard
/^#(define|ifndef).+_HPP$/ {
		print $1, gen()
		next
}

# Replace endif with generated header guard comment
/^#endif.+_HPP$/ {
		print $1, "//", gen()
		next
}

# Print the other lines
{
		print $0
}
