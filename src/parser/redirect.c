#include <parser.h>

static int	is_redirect(char c)
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

int	set_redirects(t_cmd *cmd, int **docs)
{
	int	open;

	// while (*table)
	// {
	// 	open = is_open(*table);
	// 	if (!open && is_redirect(*table))
	// 	{
	// 		if (!try_redirect(&table, cmd, docs))
	// 			return (0);
	// 		continue ;
	// 	}
	// 	else if (!open && *table == '(' && ft_memset(table, ' ', 1))
	// 		cmd->depth++;
	// 	else if (!open && *table == ')' && ft_memset(table, ' ', 1))
	// 	{
	// 		if (cmd->depth_next == -1)
	// 			cmd->depth_next = cmd->depth - 1;
	// 		else
	// 			cmd->depth_next--;
	// 	}
	// 	table++;
	// }
	return (1);
}
