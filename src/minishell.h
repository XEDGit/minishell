#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

#typedef struct s_data
{
	char	***commands;
	char	*redirects;
}	t_data;



#endif
