#!/bin/sh

rm -f file_one
if [ -f file_one ] || echo "hello" || echo " there"
then
	echo "in if"
else
	echo "in else"
fi

exit 0

