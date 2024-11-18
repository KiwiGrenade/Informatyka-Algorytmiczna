#!/bin/bash

declare -Ai word_count

svn export -r $1 $2 tempfolder > /dev/null

file_array=($(find tempfolder -type f | tr ' ' '\n'))

for i in "${file_array[@]}"
do
   if [[ -f $i ]]; then
   	word_string=$(cat $i)
   	words=($(echo "$word_string" | tr ' ' '\n'))
   	for j in "${words[@]}"
	do
		word_count[$j]=$((word_count[$j] + 1))
	done
   fi
done
for i in "${!word_count[@]}"
do
  echo "$i: ${word_count[$i]}"
done

rm -r tempfolder
