#!/bin/bash

declare word_list=$(find $1 -type f -exec cat {} \; | tr " " "\n" | sort | uniq)

for word in $word_list;
do
	echo $word
	grep -rwn $word $1
done
