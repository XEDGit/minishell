#include <executer.h>

char	*bp(char **paths, char *cmd)
{
	return (build_path(*paths - 1, cmd - 1, \
	ft_strlen(*paths) + ft_strlen(cmd) + 2));
}

int	parent_behaviour(t_cmd *start, t_data *data, pid_t child_pid)
{
	if (child_pid == -1)
		return (error_int("Error forking process", start->cmd, 1, 1));
	if (start->next && start->next->conditional != -1)
	{
		watch_child(child_pid);
		if (!reset_path(data))
			error_int("Error allocating new PATH", start->cmd, 1, 0);
	}
	return (0);
}

char	*remove_quotes_pt2(char *p, int i, int open)
{
	if (open == DOUBLE_QUOTE || open == SINGLE_QUOTE)
	{
		free(p);
		return (0);
	}
	if (p)
		p[i] = 0;
	return (p);
}
