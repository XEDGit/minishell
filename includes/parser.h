/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 16:12:02 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 19:15:05 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <shared.h>
# include <lexer.h>
# include <fcntl.h>

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
char	*get_filename(char **input);

//	redirect
int		is_redirect(char c);
int		set_pipe_cond(char *tables, t_cmd *cmd);

//	in
void	*in_redirect(char **table, t_cmd *cmd, int **docs);

//	out
void	*out_redirect(char **table, t_cmd *cmd);

int		is_del(char c);
t_var	*get_var_name(t_var *res, char *str);
int		var_name_length(char *str);

#endif
