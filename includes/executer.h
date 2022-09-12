/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:39:44 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/12 20:06:48 by lmuzio           ###   ########.fr       */
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
int		check_builtin(t_cmd *cmd, t_env *env, int piping);
int		ft_cd(char **args, t_env *env);
int		ft_echo(char **args, t_env *env);
int		ft_env(char **args, t_env *env);
int		ft_unset(char **args, t_env *env);
int		ft_export(char **args, t_env *env);
int		ft_pwd(char **args, t_env *env);

#endif