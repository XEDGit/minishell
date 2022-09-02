/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:39:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 19:17:08 by lmuzio        ########   odam.nl         */
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
void	open_pipe(t_cmd *cmd);
void	clean_redirects(t_cmd *cmd);
int		signals_handler_setup(int mode);

#endif