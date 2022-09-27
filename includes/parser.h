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
int		expander(char **tables, t_env *env);
int		count_vars(char *input);
int		vars_expansion(char **tables, t_env *env);
int		set_vars(char **vars, char *input, t_env *env);
char	*ft_tilde_expand(char **table, t_env *env);
int		clean_quotes(t_cmd *cmd);

//	file
t_file	*add_file(t_cmd *cmd);
void	free_files(t_file *lst);
char	*get_filename(char **input);

//	redirect
int	set_redirects(char *arg, t_cmd *cmd);
int	is_redirect(char c);
int	set_pipe_cond(char *tables, t_cmd *cmd);

//	in
void	*in_redirect(char **table, t_file *file);

//	out
void	*out_redirect(char **table, t_file *file);

int		is_del(char c);
t_var	*get_var_name(t_var *res, char *str);
int		var_name_length(char *str);

#endif
