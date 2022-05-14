#!/bin/zsh

ARGS=("$@")

ARGS_LEN=${#ARGS[@]}

INCLUDES=""

RED="\e[31m"

DEF="\e[39m"

I=2

PROJECT_PATH=$1

while [[ $I -lt $ARGS_LEN ]]
do
    arg=${ARGS[$I]}
	case $arg in
        "-e")
			EXCLUDE+="! -path '*${ARGS[$I + 1]}*' "
        ;;

        "-i")
			INCLUDES+="-I$PROJECT_PATH/${ARGS[$I + 1]} "
        ;;

        "-readline")
			READLINE_INCLUDES=" -lreadline -L${ARGS[I + 1]}/lib -I${ARGS[I + 1]}/include"
        ;;

        "-h")
			printf "INFO: Put the folder inside your project root\nUsage: ./malloc_wrapper project_path [-h] [-e exclude_folder_name] [-i include_flag] [-readline library_path]"
            exit
        ;;
    esac
    (( I = I + 1 ))
done

eval "cat << EOF > $PROJECT_PATH/fake_malloc.c
#include <dlfcn.h>
#include <execinfo.h>
#include <stdio.h>

#define RED \"\e[31m\"

#define DEF \"\e[39m\"

int	malloc_hook_backtrace_readable(char ***stack_readable)
{
	void	*stack[10];
	int		stack_size;

	stack_size = backtrace(stack, 10);
	*stack_readable = backtrace_symbols(stack, stack_size);
	return (stack_size);
}

void	malloc_hook_string_edit(char *str)
{
	str = &str[59];
	while (*str && *str != ' ')
		str++;
	*str = 0;
}

void	*malloc(size_t size)
{
	void	*ret;
	char	**stack;
	int		stack_size;
	void	(*og_free)(void *);
	void	*(*og_malloc)(size_t);

	og_malloc = dlsym(RTLD_NEXT, \"malloc\");
	og_free = dlsym(RTLD_NEXT, \"free\");
	ret = og_malloc(size);
	stack_size = malloc_hook_backtrace_readable(&stack);
	malloc_hook_string_edit(stack[2]);
	malloc_hook_string_edit(stack[3]);
	printf(RED \"(MALLOC_WRAPPER) %s - %s allocated %zu bytes at %p\n\" DEF, \
	&stack[3][59], &stack[2][59], size, ret);
	og_free(stack);
	return (ret);
}

void	free(void *tofree)
{
	char	**stack;
	void	(*og_free)(void *);

	og_free = dlsym(RTLD_NEXT, \"free\");
	malloc_hook_backtrace_readable(&stack);
	malloc_hook_string_edit(stack[2]);
	malloc_hook_string_edit(stack[3]);
	printf(RED \"(FREE_WRAPPER) %s/%s free %p\n\" DEF, \
	&stack[3][59], &stack[2][59], tofree);
	og_free(stack);
	og_free(tofree);
}

EOF"

SRC=$(eval "find $PROJECT_PATH -name '*.c' $EXCLUDE" | tr '\n' ' ')

GCC_COMMAND="gcc $SRC -rdynamic -o malloc_debug $INCLUDES $READLINE_INCLUDES"
printf "$RED$GCC_COMMAND$DEF\n"
eval $GCC_COMMAND
rm "$PROJECT_PATH/fake_malloc.c"
if [[ $? == 0 ]]
then
    printf "$RED Success$DEF\n"
else
    exit
fi
printf "$RED./malloc_debug:$DEF\n"
./malloc_debug
rm ./malloc_debug