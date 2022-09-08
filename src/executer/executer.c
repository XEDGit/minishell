/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/04 03:37:21 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	execute_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	execve(cmd->cmd, cmd->args, envp);
}

int     watch_child(void)
{
        int     statbuf;
        int     exit_code;

        while (wait(&statbuf) != -1)
                ;
        if (WIFSIGNALED(statbuf))
                exit_code = WTERMSIG(statbuf);
        else
                exit_code = WEXITSTATUS(statbuf);
        return (exit_code);
}

int	parse_cmd(t_cmd *start, char **envp)
{
	pid_t	child_pid;

	start->cmd = start->args[0];
	if (start->is_pipe && open_pipe(start))
		return (error_int("pipe command failed\n", 0));
	child_pid = fork();
	if (!child_pid)
		execute_cmd(start, envp);
	if (start->next && start->next->conditional != -1)
		g_exit_code = watch_child();
	clean_redirects(start);
	return (0);
}

int	executer(t_data *data)
{
	char	*new_cmd;
	t_cmd	*start;
	int		builtin;

	data->paths = ft_split(getenv("PATH"), ":");
	start = data->cmds;
	signals_handler_setup(1);
	while (start)
	{
		builtin = 0;
		builtin = check_builtin(data->cmds);
		if (builtin == 2)
			return (1);
		if (!builtin)
		{
			start->args[0] = check_paths(data->paths, start->cmd);
			if (start->args[0] != NULL)
				parse_cmd(start, data->envp);
		}
		start = start->next;
	}
	g_exit_code = watch_child();
	signals_handler_setup(0);
	return (0);
}
