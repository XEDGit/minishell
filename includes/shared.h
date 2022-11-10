/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:43:30 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/31 16:12:08 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

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
# define SHELLNAME "SkiruSh: "

// internal
# include <ft_libc.h>
# include <structs.h>
# include <ft_printf.h>

// external
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_code;

void	*error_msg(char *msg, int exit_code);
int		error_int(char *msg, char *cmd, int exit_code, int return_val);
int		error_free2d(void *tofree);
int		error_free2dint(void *tofree, int len, int ret);
int		error_free(void *tofree);
int		signals_handler_setup(int mode);
int		free2d(char **tofree, int len);
int		free2dint(int **tofree, int len);
int		lexer(char *input, t_env *env);
int		parser(char **tables, t_data *data);
int		executer(t_data *data);

#endif
