/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:25:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/08/04 22:08:29 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <ft_libc.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <ft_printf.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				redirects[3];
	int				is_pipe;
	int				depth;
	int				depth_next;
	int				conditional;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmds;
	int		**heredocs;
	int		heredoc_c;
	char	*input;
	char	**paths;
}	t_data;

# define ERROR -1
# define AND 100
# define OR 101
# define PIPE '|'
# define AMP '&'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define PARENTHESIS ')'
# define NEW_LINE '\n'
# define TITLE "\001\e[31;1m\002 SKIRU ~> \001\e[0m\002"

int		signals_handler_setup(void);
int		lexer(char *input, t_data *data);
int		dchar_check(char *input, char ch);
int		semicolon_check(char *input);
int		pipe_check(char *input);
int		lexer_multiline_check(char *in, int delimiter);
int		parenthesis_check(char *input);
int		heredoc_check(char *input, t_data *data);
int		heredoc_repeat(char *input, int *fds);
char	*extract_pipe(int fd);
char	*remove_quotes(char *input);
int		parser(char **tables, t_data *data);
void	*error_msg(char *msg);
int		error_int(char *msg, int exit_code);
int		error_free2d(void *tofree);
int		error_free2dint(void *tofree);
int		error_free(void *tofree);
int		free2d(char **tofree, int len);
int		free2dint(int **tofree, int len);
int		skip_quotes(char *input);
int		is_open(char c);
int		syntax_check(char *input, t_data *data);
int		check_double_commands(char *str, int c, int diff);

// command
t_cmd	*add_cmd(t_cmd **start);
int		free_cmds(t_cmd *start, char **tables, int exit_code);
int		debug_cmds(t_cmd *start);

#endif
