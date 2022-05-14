#!/bin/bash

PROJECT_PATH=".."

ARGS=("$@")

ARGS_LEN=${#ARGS[@]}

INCLUDES=""

I=0

while [[ $I -lt $ARGS_LEN ]]
do
    arg=${ARGS[$I]}
	case $arg in
        "-e")
			EXCLUDE=${ARGS[$I + 1]}
        ;;

        "-p")
			PROJECT_PATH=${ARGS[$I + 1]}
        ;;

        "-i")
			INCLUDES+="-I$PROJECT_PATH/${ARGS[$I + 1]} "
        ;;
    esac
    (( I = I + 1 ))
done

SRC=$(find $PROJECT_PATH ! -path "*$EXCLUDE*" -name '*.c')

COMMAND=$(echo "gcc malloc_hook.c $SRC -rdynamic -o malloc_debug -lreadline -L/usr/local/opt/readline/lib $INCLUDES -I/usr/local/opt/readline/include" | tr "\n" " ")
printf "$COMMAND\n"
$COMMAND
if [[ $? == 0 ]]
then
    printf "Success\n"
fi
printf "./malloc_debug:\n"
./malloc_debug
rm ./malloc_debug