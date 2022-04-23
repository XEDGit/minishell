# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester_orig.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 21:13:54 by lmuzio            #+#    #+#              #
#    Updated: 2022/04/23 22:59:26 by lmuzio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ERROR="\e[1;31m"

MAGENTA="\e[1;35m"

BOLD="\e[1m"

OUTPUT_END="\e[30;47m"

RESET="\e[0m"

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

		"-a")
			(( I = I + 1 ))
			while [[ $I -lt $ARGS_LEN ]]
			do
				if [[ ${ARGS[$I]} = "-"* ]]
				then
					(( I = I - 1 ))
					break
				fi
				OUT_ARGS+=(${ARGS[$I]})
				(( I = I + 1 ))
			done
		;;

		"-d")
			MAX_DEPTH=${ARGS[$I + 1]}
		;;

		"-h")
			printf "Usage: tester [-h] [-a arg1 [arg2] [arg...]] [-d max_depth]\n" >&2
			exit 0
		;;
	esac
	(( I = I + 1 ))
done

#	EXECUTION
SRCS=$(find . -name '*.c' -maxdepth $MAX_DEPTH )
C=0
C2=0

#	No files error
if [ -z "$SRCS" ]
then
	printf "${ERROR}Error: No supported files (.c)\n$RESET" >&2
	exit 1
fi

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

printf "\n\n$MAGENTA\nOutput:\n____________________\n$RESET"

#	Compiling chosen file
printf "gcc $FILE -o output\n"
gcc "$FILE" -o output

#	Running and cleaning if compiling exited with status 0
if [ $? = 0 ]
then
	if [ ${#SRCS[@]} != 0 ]
	then
		printf "$FILE ${OUT_ARGS[@]}\n\n"
		./output ${OUT_ARGS[@]}
	else
		./output
	fi
	rm output
fi

#	Output outline
printf "$OUTPUT_END%%$RESET$MAGENTA\n____________________\n$RESET"