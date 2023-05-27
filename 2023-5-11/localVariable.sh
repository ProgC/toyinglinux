#!/bin/sh

sample_text="global variable"

foo() {
	local sample_text="local variable";
	echo "function foo is executing"
	echo $sample_text
}

echo "script start"
echo $sample_text
foo

echo "script end"
echo $sample_text

exit 0

