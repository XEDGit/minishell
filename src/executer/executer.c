/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 00:25:49 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	execute_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	execve(cmd->cmd, cmd->args, envp);
}

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
}

int	parse_cmd(t_cmd *start, char **envp, char **paths)
{
	pid_t	child_pid;

	start->args[0] = check_paths(paths, start->cmd);
	start->cmd = start->args[0];
	if (start->is_pipe && open_pipe(start))
		return (false);
	if (start->args[0])
	{
		child_pid = fork();
		if (!child_pid)
			execute_cmd(start, envp);
		if (start->next && start->next->conditional != -1)
			watch_child(child_pid);
	}
	clean_redirects(start);
	return (child_pid);
}

int	executer_loop(t_cmd *start, t_data *data)
{
	int		builtin;
	int		piping;
	pid_t	child_pid;

	piping = 0;
	while (start)
	{
		if (start->is_pipe)
			piping = start->is_pipe;
		if (start->conditional != -1)
			piping = 0;
		builtin = 0;
		builtin = check_builtin(start, data->envp, data->envl, piping);
		if (builtin == 2)
			return (true);
		if (!builtin)
			child_pid = parse_cmd(start, data->envp, data->paths);
		start = start->next;
	}
	watch_child(child_pid);
	return (false);
}

int	executer(t_data *data)
{
	int		piping;
	pid_t	child_pid;
	t_cmd	*start;
	char	*paths;

	paths = ft_get_env(data->envp, "PATH");
	data->paths = ft_split(paths, ":");
	free(paths);
	start = data->cmds;
	signals_handler_setup(1);
	if (executer_loop(start, data))
		return (2);
	signals_handler_setup(0);
	return (0);
}
