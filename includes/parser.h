#ifndef PARSER_H
# define PARSER_H

#include <minishell.h>
#include <fcntl.h>

# define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

//	redirect
char	*set_redirects(char *table, t_cmd *cmd, int **docs);

//	in
int		left_rdrt(char *inp, t_cmd *cmd);
int		here_doc(char *inp, t_cmd *cmd, int ** docs);

//	out
int		right_rdrt(char *inp, t_cmd *cmd);
int		append(char *inp, t_cmd *cmd);

#endif
