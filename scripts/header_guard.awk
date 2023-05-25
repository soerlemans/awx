#!/usr/bin/env -S gawk -i inplace -f 


# Generate header guard
function gen()
{
	guard = toupper(FILENAME)
	gsub(/(\/)|(\.)/, "_", guard)
	gsub("SRC", "AWX", guard)

	return guard
}

/^#(define)|(ifndef).+_HPP$/ {
		print $1, gen()
		next
}

/^#endif.+_HPP$/ {
		print $1, "//", gen()
		next
}

{
		print $0
}
