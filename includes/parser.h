#ifndef PARSER_H
# define PARSER_H

#include <minishell.h>
#include <fcntl.h>

# define PARSE_DEBUG 1
# define LEFT_REDIRECT '<'
# define RIGHT_REDIRECT '>'
# define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

typedef struct s_var
{
	char	*p;
	int		length;
	char	c;
}	t_var;

//	expand
int		expander(char **tables, t_cmd *cmd);

//	file
char    *get_filename(char **input);

//	redirect
int		set_redirects(char *table, t_cmd *cmd, int **docs);

//	redirect
int		set_pipe_cond(char *tables, t_cmd *cmd);

//	in
void	*in_redirect(char **table, t_cmd *cmd, int **docs);

//	out
void	*out_redirect(char **table, t_cmd *cmd);

int	is_del(char c);
t_var	*get_var_name(t_var *res, char *str);
int	var_name_length(char *str);

#endif
