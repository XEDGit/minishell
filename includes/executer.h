/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:39:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/07 22:01:23 by xed           ########   odam.nl         */
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

void	watch_child(pid_t pid);
char	*check_paths(char **paths, char *cmd);
int		open_pipe(t_cmd *cmd);
int		clean_redirects(t_cmd *cmd);
int		signals_handler_setup(int mode);
int		check_builtin(t_cmd *cmd, char **envp, char **envl, int piping);
int		ft_cd(char **args, char **envp, char **envl);
int		ft_echo(char **args, char **envp, char **envl);
int		ft_env(char **args, char **envp, char **envl);
int		ft_unset(char **args, char **envp, char **envl);
int		ft_export(char **args, char **envp, char **envl);
int		ft_pwd(char **args, char **envp, char **envl);

#endif