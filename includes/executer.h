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

int		reset_path(t_data *data);
char	*check_paths(char **paths, char *cmd);
int		open_files(t_cmd *cmd, t_data *data);
int		open_pipe(t_cmd *cmd);
int		clean_redirects(t_cmd *cmd);
int		set_redirects(t_cmd *cmd, int **docs);
int		signals_handler_setup(int mode);
int		check_builtin(t_cmd *cmd, t_data *data, int piping);
int 	check_aliases(t_cmd *cmd, t_env *aliases);
int	    sk_alias(t_cmd *cmd, t_data *data);
int     sk_exec(t_cmd *cmd, t_data *data);
int		sk_cd(t_cmd *cmd, t_data *data);
int		sk_echo(t_cmd *cmd, t_data *data);
int		sk_env(t_cmd *cmd, t_data *data);
int		sk_unset(t_cmd *cmd, t_data *data);
int		sk_export(t_cmd *cmd, t_data *data);
int		sk_pwd(t_cmd *cmd, t_data *data);
int		sk_exit(t_cmd *cmd);
int		parent_behaviour(t_cmd *start, t_data *data, pid_t child_pid);
char	*build_path(char *temp_path, char *temp_cmd, int len);
char	*bp(char **paths, char *cmd);

#endif