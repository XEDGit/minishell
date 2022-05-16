/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:25:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/16 03:14:30 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "../src/ft_printf/ft_printf.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				redirects[3];
	int				par_depth;
	int				conditional;
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

# define TRUE 0
# define FALSE 1
# define ERROR -1
# define AND 100
# define OR 101
# define PIPE 124
# define AMP 38
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PARENTHESIS 41
# define NEW_LINE 10
# define TITLE "\001\e[31;1m\002 SKIRU ~> \001\e[0m\002"

int		signals_handler_setup(void);
int		lexer(char *input);
int		ampersand_check(char *input);
int		pipe_check(char *input);
int		heredoc_check(char *input, t_data *data);
int		heredoc_repeat(char *input, int *fds);
char	*extract_pipe(int fd);
char	*remove_quotes(char *input);
int		parser(char **tables, t_data *data);
char	**ft_split(char const *s, char *c);
int		free2d(char **tofree, int len);
int		free2dint(int **tofree, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strclen_no_quotes(const char *start, const char *end);
size_t	ft_strclen(const char *start, const char *end);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strexcmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int str);
int		skip_quotes(char *input);

#endif
