/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:25:56 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/09 17:14:24 by lmuzio           ###   ########.fr       */
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
	int				parth_depth;
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
# define ERROR 2
# define AND 100
# define OR 101
# define PIPE 124
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

int		signals_handler_setup(void);
int		lexer(char *input);
int		ft_isspace(int str);
char	**ft_split(char const *s, char *c);
char	**free2d(char **tofree, int len);

#endif
