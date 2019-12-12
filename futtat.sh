#!/bin/bash

cat input.txt | ./a.out > output.txt

result=$(diff -bB output.txt sample.txt)

if [ -z "$result" ]
then
	echo "A teszt sikeres volt!"
else
	echo "A teszt sikertelen :("
fi
