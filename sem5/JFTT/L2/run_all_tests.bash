#!/bin/bash
DIR_LIST=("ex1" "ex2" "ex3")
for DIR in "${DIR_LIST[@]}"
do
    echo "Tests for $DIR:"
	cd $DIR
    make
    bash tester.bash
    cd ..
done