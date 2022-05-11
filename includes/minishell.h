/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:25:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 04:42:11 by lmuzio        ########   odam.nl         */
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
# define TITLE "\001\e[31;1m\002 SKIRU ~> \001\e[0m\002"

int		signals_handler_setup(void);
int		lexer(char *input);
int		parser(char **tables);
char	**ft_split(char const *s, char *c);
int		free2d(char **tofree, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strclen(const char *start, const char *end);
size_t	ft_strclen(const char *start, const char *end);
size_t	ft_strlen(const char *str);
int		ft_isspace(int str);

#endif
