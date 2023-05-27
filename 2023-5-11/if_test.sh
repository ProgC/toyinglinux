#!/bin/sh

foo()
{
	# like C, 0 means true otherwise false (for all positive numbers)
	# return 0 means true
	# return 1 means false
	# return 2 means false
	# return 123 means false
	return 123;
}

if foo
then
	echo "true"
else
	echo "false"
fi

exit 0

