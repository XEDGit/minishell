#ifndef PARSER_H
# define PARSER_H

#include <minishell.h>
#include <fcntl.h>

# define LEFT_REDIRECT '<'
# define RIGHT_REDIRECT '>'
# define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

//	file
char    *get_filename(char **input);

//	redirect
char	*set_redirects(char *table, t_cmd *cmd, int **docs);

//	in
void	*in_redirect(char **table, t_cmd *cmd, int **docs);

//	out
void	*out_redirect(char **table, t_cmd *cmd);

#endif
