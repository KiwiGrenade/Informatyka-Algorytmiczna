#!/bin/sh
#Author: Jakub Jaśków

x=0
echo "PID:?COMM:?STATE:?PPID:?PGRP:?SESSION:?TTY:?RSS:?NOF:?" >> lista
for i in $(find /proc/*/stat -maxdepth 0 -type f);
do
{
	NWORDS=$(wc -w < $i)
	OFFSET=$((NWORDS-52))
	LIMITER=$((7+OFFSET))
	POINT=$((23+OFFSET))
	for j in $(cat $i)
	do
	{
		NUMBER=$((1+OFFSET))
		if [ $x -lt $LIMITER ] || [ $x -eq $POINT ]
		then
			if [ $LIMITER -gt 0 ] && [ $x -lt $NUMBER ] && [ $x -gt 0 ]
			then
				echo -n "$j " >> lista
			else
				echo -n "$j?" >> lista
			fi
		fi
		x=$((x+1))
	};
	done
	PARENT=$(dirname $i)
	echo -n $(ls "$PARENT/fd" | wc -l) >> lista
	x=0
	echo "\n" >> lista
};
done
column -t -s ? lista
rm lista
exit
