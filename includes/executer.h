/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:37:20 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 17:02:50 by nmolinel      ########   odam.nl         */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	watch_child(pid_t pid);
int		reset_path(t_data *data);
char	*check_paths(char **paths, char *cmd);
int		open_files(t_cmd *cmd, t_data *data);
int		open_pipe(t_cmd *cmd);
int		clean_redirects(t_cmd *cmd);
int		set_redirects(t_cmd *cmd, int **docs);
int		signals_handler_setup(int mode);
int		check_builtin(t_cmd *cmd, t_data *data, int piping);
int		ft_cd(char **args, t_env *env);
int		ft_echo(char **args, t_env *env);
int		ft_env(char **args, t_env *env);
int		ft_unset(char **args, t_env *env);
int		ft_export(char **args, t_env *env);
int		ft_pwd(char **args, t_env *env);
int		ft_exit(t_cmd *cmd);
int	    parent_behaviour(t_cmd *start, t_data *data, pid_t child_pid);
char	*build_path(char *temp_path, char *temp_cmd, int len);
char	*bp(char **paths, char *cmd);

#endif