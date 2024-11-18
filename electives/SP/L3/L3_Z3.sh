#!/bin/bash

declare -A word_count

svn export -r $1 $2 tempfolder > /dev/null

file_array=($(find tempfolder -type f | tr ' ' '\n'))

for i in "${file_array[@]}"
do
   if [[ -f $i ]]; then
   	word_string=$(cat $i)
   	words=($(echo "$word_string" | tr ' ' '\n'))
   	declare -a already_counted=() #already counted words in i-th file
   	for j in "${words[@]}"
	do
		if [[ ! " ${already_counted[*]} " =~ " ${j} " ]]; then
			word_count[$j]=$((word_count[$j] + 1))
			already_counted[${#already_counted[@]}]="$j"
		fi
	done
   fi
done
for i in "${!word_count[@]}"
do
  echo "$i: ${word_count[$i]}"
done

rm -r tempfolder
