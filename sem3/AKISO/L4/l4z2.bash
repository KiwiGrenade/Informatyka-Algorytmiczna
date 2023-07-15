#!/bin/bash
INTERFACE=wlp3s0
d1=$(cat /sys/class/net/wlp3s0/statistics/rx_bytes)
u1=$(cat /sys/class/net/wlp3s0/statistics/tx_bytes)


declare -a IDLE_TIME
declare -a IDLE_OLD_TIME
declare -a SUMS
declare -a SUMS_OLD
declare -a CPU_NAME
declare -a CPU_USAGE
touch avgdownload.txt
touch avgupload.txt

printDownSpeed()
{
	d2=$(cat /sys/class/net/wlp3s0/statistics/rx_bytes)
	DOWN=$((d2-d1))
	AVG_DOWN=0
	if [ $DOWN -gt 0 ]
	then
		echo >> avgdownload.txt $DOWN
	fi
	
	if [ -s avgdownload.txt ]
	then	
		AVG_DOWN=$(awk '{sum += $1} END { printf("%.0f", sum/NR)  }' avgdownload.txt)
	fi

	DOWN_SUFFIX="B/s"
	if [ $DOWN -gt 1024 ] #1024 * 1024
	then
		DOWN=$((DOWN/1024))
		DOWN_SUFFIX="KB/s"
	fi
	if [ $DOWN -gt 1024 ]
	then
		DOWN=$((DOWN/1024))
		DOWN_SUFFIX="MB/s"
	fi

	AVG_DOWN_SUFFIX="B\s"
	if [ $AVG_DOWN -gt 1024 ]
	then 
		AVG_DOWN=$((AVG_DOWN/1024))
		AVG_DOWN_SUFFIX="KB/s"
	fi
	if [ $AVG_DOWN -gt 1024 ]
	then
		AVG_DOWN=$((AVG_DOWN/1024))
		AVG_DOWN_SUFFIX="MB/s"
	fi
	
	echo "DOWN SPEED: $DOWN $DOWN_SUFFIX"	
	echo "AVG DOWN SPEED: $AVG_DOWN $AVG_DOWN_SUFFIX"
	d1=$d2
}

printUpSpeed()
{
	u2=$(cat /sys/class/net/wlp3s0/statistics/tx_bytes)
	UP=$((u2-u1))
	AVG_UP=0
	if [ $UP -gt 0 ]
	then
		echo >> avgupload.txt $UP
	fi
	if [ -s avgupload.txt ]
	then	
		AVG_UP=$(awk '{sum += $1} END { printf("%.0f", sum/NR)  }' avgupload.txt)
	fi
	UP_SUFFIX="B/s"
	AVG_UP_SUFFIX="B/s"
	
	if [ $UP -gt 1024 ] #1024 * 1024
	then
		UP=$((UP/1024))
		UP_SUFFIX="KB/s"
	fi
	if [ $UP -gt 1024 ]
	then
		UP=$((UP/1024))
		UP_SUFFIX="MB/s"
	fi

	if [ $AVG_UP -gt 1024 ]
	then 
		AVG_UP=$((AVG_UP/1024))
		AVG_UP_SUFFIX="KB/s"
	fi
	if [ $AVG_UP -gt 1024 ]
	then
		AVG_UP=$((AVG_UP/1024))
		AVG_UP_SUFFIX="MB/s"
	fi
	
	echo "UP SPEED:   $UP $UP_SUFFIX"
	echo "AVG UP SPEED: $AVG_UP $AVG_UP_SUFFIX"
	u1=$u2
}

getCpuInfo()
{
	IDLE_OLD_TIME=("${IDLE_TIME[@]}")
	SUMS_OLD=("${SUMS[@]}")
	local x=0
	local CPU_NUMBER=0
	
	#reset variables
	SUMS=()
	IDLE_TIME=()
	
	for i in $(cat /proc/stat | grep cpu)
	do
	{
	
		if [ $x -eq 11 ]
		then
			x=0
			CPU_NUMBER=$((CPU_NUMBER+1))
		fi	
		
		if [ $x -eq 0 ] 
		then
			CPU_NAME[$CPU_NUMBER]=$i
		fi

		if [ $x -lt 12 ]
		then
			SUMS[$CPU_NUMBER]=$((${SUMS[$CPU_NUMBER]}+i))	
			if [ $x -eq 4 ]
			then
				IDLE_TIME[$CPU_NUMBER]=$i
			fi	
		fi
		x=$((x+1))
	};done

}

printCpuUsage()
{
	getCpuInfo

	local NOT_USED_PERCENT
	local LENGTH=${#CPU_NAME[@]}
	local DELTA_SUM
	local DELTA_IDLE

	for i in `seq 0 $((LENGTH-1))`
	do
	{
		local OLD_SUM=${SUMS_OLD[$i]}
		local NEW_SUM=${SUMS[$i]}
		DELTA_SUM=$((NEW_SUM-OLD_SUM))
		
		local OLD_IDLE=${IDLE_OLD_TIME[$i]}
		local NEW_IDLE=${IDLE_TIME[$i]}
		DELTA_IDLE=$((NEW_IDLE-OLD_IDLE))

		NOT_USED_PERCENT=$((DELTA_IDLE*100/DELTA_SUM))
		USED_PERCENT=$((100-NOT_USED_PERCENT))
		echo -n "${CPU_NAME[$i]}: $USED_PERCENT% "
	};done
	echo ""
}

printCpuFrequency()
{
	local x=0
	for i in $(grep 'processor\|cpu\ MHz' /proc/cpuinfo)
	do
	{
		if [ $x -lt 7 ]
		then
			echo -n "$i " >> demo
		else
			echo "" >> demo
			x=0
		fi
		x=$((x+1))
	};done
	column -t -s : demo
	rm demo
}
printUptime()
{
	awk '{print "\nUPTIME: " int($1/86400)"d "int(($1%86400)/3600)"h "int((($1%86400)%3600)/60)"m "int((($1%86400)%3600)%60)"s"}' /proc/uptime
}

printBatteryLevel ()
{
	awk '{print "BATTERY LEVEL: " $1 "%"}' /sys/class/power_supply/BAT0/capacity
}

printAvgLoad()
{
	awk '{print "AVG LOAD PER: "$1"-1min "$2"-5min "$3"-15min"}' /proc/loadavg
}

printMemInfo()
{
	printf "$(grep Mem /proc/meminfo)"
}

while sleep 1
do
{
	clear
	printDownSpeed
	printUpSpeed		
	printCpuUsage
	printCpuFrequency
	printUptime
	printBatteryLevel
	printAvgLoad	
	printMemInfo


};done

rm avgdownload.txt
rm avgupload.txt
