/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:36:19 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 00:45:12 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	watch_child(pid_t pid)
{
	int	statbuf;
	int	exit_code;

	if (waitpid(pid, &statbuf, 0) != pid)
		return ;
	if (WIFEXITED(statbuf))
	{
		if (WIFSIGNALED(statbuf))
			g_exit_code = WTERMSIG(statbuf);
		else
			g_exit_code = WEXITSTATUS(statbuf);
	}
	while (wait(0) != -1)
		;
}