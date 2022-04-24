#!/bin/bash

ERROR="\e[1;31m"

MAGENTA="\e[1;35m"

BOLD="\e[1m"

OUTPUT_END="\e[30;47m"

RESET="\e[0m"

RE='^[0-9]+$'

# OPTIONS

ARGS=("$@")

ARGS_LEN=${#ARGS[@]}

MAX_DEPTH=1

I=0

OUT_ARGS=()

#	Loop through arguments array and search for options
while [[ $I -lt $ARGS_LEN ]]
do
	arg=${ARGS[$I]}
	case $arg in

		#	-a option will accept its arguments as the arguments of the executable when launched
		"-a")
			(( I = I + 1 ))
			while [[ $I -lt $ARGS_LEN ]]
			do
				if [[ ${ARGS[$I]} = "-"* ]]
				then
					(( I = I - 1 ))
					break
				fi
				OUT_ARGS+=("${ARGS[$I]}")
				(( I = I + 1 ))
			done
		;;

		#	-d option sets the maximum depth of the find command
		"-d")
			NEW_VAL=${ARGS[$I + 1]}
			if ! [[ $NEW_VAL =~ $RE ]]
			then
				printf "Error: $arg argument is not a number"
				exit 1
			fi
			MAX_DEPTH=$NEW_VAL
		;;

		#	-o option lets the user skip the file choice by presetting $TO_TEST
		"-o")
			NEW_VAL=${ARGS[$I + 1]}
			if ! [[ $NEW_VAL =~ $RE ]]
			then
				printf "Error: $arg argument is not a number"
				exit 1
			fi
			TO_TEST=$NEW_VAL
		;;

		"-f")

		;;

		"-h")
			printf "Usage: tester [-h] [-a arg1 [arg2] [arg...]] [-d max_depth] [-o ]\n" >&2
			exit 0
		;;

	esac
	(( I = I + 1 ))
done

#	EXECUTION
SRCS=$(find . -maxdepth $MAX_DEPTH -name '*.c'  )

C=0

C2=0

#	No files error
if [ -z "$SRCS" ]
then
	printf "${ERROR}Error: No supported files (.c)\n$RESET" >&2
	exit 1
fi

if [ -z "$TO_TEST" ]
then
	#	Intro message
	printf "Which file do you want to run?\n\n$MAGENTA"

	#	File listing
	for f in $SRCS
	do
		(( C = C + 1 ))
		printf "  $C) $f\n"
	done

	#	User input
	printf "$RESET\nSelect a number: "
	read -rn1 TO_TEST 

	# 	Exit conditions
	if [[ $TO_TEST == q || $TO_TEST == $(printf "\e") ]]
	then
		printf "\n"
		exit 0
	else
		printf "\n\n"
	fi
fi

#	find input into file list
for f in $SRCS
do
	(( C2 = C2 + 1 ))
	if [[ $C2 -eq $TO_TEST ]]
	then
		FILE=$f
	fi
done

#	check if input is found
if [ -z "$FILE" ]
then
	printf "\n${ERROR}Error: Insert a number between 1 and $C$RESET\n" >&2
	exit 1
fi

#	Output outline

printf "${MAGENTA}Output:\n$RESET"
printf "gcc $FILE -o output${MAGENTA}\n____________________\n$RESET"

#	Compiling chosen file
gcc "$FILE" -o output

#	Running and cleaning if compiling exited with status 0
if [ $? = 0 ]
then
	printf "Success\n\n"
	if [ ${#OUT_ARGS[@]} != 0 ]
	then
		printf "$FILE ${OUT_ARGS[*]}$MAGENTA\n____________________\n$RESET"
		./output ${OUT_ARGS[*]}
	else
		printf "$FILE$MAGENTA\n____________________\n$RESET"
		./output
	fi
	rm -f ./output
fi

#	Output outline
printf "$OUTPUT_END%%$RESET\n"
