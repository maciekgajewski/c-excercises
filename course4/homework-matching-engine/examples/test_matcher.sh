#!/bin/bash
#
# Automated test foe a maching engine
#
# Run in this directory, pass the matching engine binary as the first argument

ENGINE=$1

for test_input in *.in
do
	test=`basename $test_input .in`
	expected_output=${test}.out
	echo Testing $test ...
	out=`mktemp`
	$ENGINE < $test_input > $out
	DIFF=`diff -q -B $expected_output $out`
	if [ -z "$DIFF" ]
	then
		echo OK
	else
		echo failed. differneces:
		diff -u $expected_output $out
	fi
	rm $out
done

