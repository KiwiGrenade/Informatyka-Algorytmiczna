#!/bin/bash

declare -Ai words

for file in $(find $1 -type f);
do
	for word in $(cat $file | tr " " "\n" | sort | uniq);
	do
		words[$word]+=1
	done
done

for word in ${!words[@]};
do
	echo "$word ${words[$word]}"
done
