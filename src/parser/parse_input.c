#include "minishell.h"

int parser_main(int argc, char **argv)
{
    int temp;

    while (++*argv)
        metachars();
    check_executable(argv[0]);

}
