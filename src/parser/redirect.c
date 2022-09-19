#include <parser.h>

int	is_redirect(char c)
{
	if (c == LEFT_REDIRECT)
		return (LEFT_REDIRECT);
	else if (c == RIGHT_REDIRECT)
		return (RIGHT_REDIRECT);
	return (0);
}

static int	try_redirect(char **table, t_cmd *cmd, int **docs)
{
	char	*from;
	void	*red;

	from = *table;
	if (**table == RIGHT_REDIRECT)
		red = out_redirect(table, cmd);
	else if (**table == LEFT_REDIRECT)
		red = in_redirect(table, cmd, docs);
	if (!red)
		return (0);
	ft_memset(from, ' ', *table - from);
	return (1);
}

static int check_redirect(char *arg, t_cmd *cmd, int **docs)
{
	int		open;

	while (*arg)
	{
		open = is_open(*arg);
		if (!open && is_redirect(*arg))
		{
			if (!try_redirect(&arg, cmd, docs))
				return (0);
			continue ;
		}
		else if (!open && *arg == '(' && ft_memset(arg, ' ', 1))
			cmd->depth++;
		else if (!open && *arg == ')' && ft_memset(arg, ' ', 1))
		{
			if (cmd->depth_next == -1)
				cmd->depth_next = cmd->depth - 1;
			else
				cmd->depth_next--;
		}
		arg++;
	}
	return (1);
}

int	is_valuable(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str++ != ' ')
			i++;
	}
	return (i);
}

void shift_arg(char **args, int index)
{
	int	i;

	i = index;
	free(args[i]);
	args[i] = 0;
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		args[++i] = 0;
	}
}

void	clean_args(t_cmd *cmd, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		//	TODO: trim args from extra spaces,
		//	caused by resolving redirects
		
		if (!is_valuable(args[i]))
			shift_arg(args, i--);
		i++;
	}
	cmd->cmd = args[0];
}

int	set_redirects(t_cmd *cmd, int **docs)
{
	int		i;
	char	*arg;

	i = 0;
	while (cmd->args[i])
	{
		if (!check_redirect(cmd->args[i], cmd, docs))
			return (0);
		i++;
	}
	clean_args(cmd, cmd->args);
	return (1);
}
