/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:39:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/04 03:49:46 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

// internal
# include <shared.h>

// external
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>

char	*check_paths(char **paths, char *cmd);
int		open_pipe(t_cmd *cmd);
int		clean_redirects(t_cmd *cmd);
int		signals_handler_setup(int mode);
int		check_builtin(t_cmd *cmd);
void	ft_cd(char **args);
void	ft_echo(char **args);
void	ft_env(char **args);
void	ft_unset(char **args);
void	ft_export(char **args);
void	ft_pwd(char **args);

#endif