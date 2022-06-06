/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:25:56 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/17 17:27:01 by lmuzio           ###   ########.fr       */
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
# include <stdbool.h>
# include <ft_printf.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				redirects[3];
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
int		lexer(char *input);
int		dchar_check(char *input, char ch);
int		semicolon_check(char *input);
int		pipe_check(char *input);
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
char	**ft_split(char const *s, char *c);
int		free2d(char **tofree, int len);
int		free2dint(int **tofree, int len);
int		ft_strjoin(char **s1, char const *s2);
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

// command
t_cmd	*add_cmd(t_cmd **start);
int		free_cmds(t_cmd *start, char **tables, int exit_code);
int		debug_cmds(t_cmd *start);

#endif
