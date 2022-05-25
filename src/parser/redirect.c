#include <parser.h>

//	return true if inside unclosed quotes
static int	is_open(char c)
{
	static int	open = 0;

	if (!open && c == SINGLE_QUOTE)
		open = SINGLE_QUOTE;
	else if (!open && c == DOUBLE_QUOTE)
		open = DOUBLE_QUOTE;
	else if (open == SINGLE_QUOTE && c == SINGLE_QUOTE)
		open = 0;
	else if (open == DOUBLE_QUOTE && c == DOUBLE_QUOTE)
		open = 0;
	return (open);
}

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
	if (**table == RIGHT_REDIRECT)
	{
		if (!out_redirect(table, cmd))
			return (0);
	}
	else if (**table == LEFT_REDIRECT)
	{
		if (!in_redirect(table, cmd, docs))
			return (0);
	}
	return (1);
}

char	*set_redirects(char *table, t_cmd *cmd, int **docs)
{
	char	*rest;
	int		counter;
	
	counter = 0;
	rest = malloc(sizeof(char) * (ft_strlen(table) + 1));
	if (!rest)
		return (0);
	while (*table)
	{
		if (!is_open(*table) && is_redirect(*table))
		{
			if (!try_redirect(&table, cmd, docs))
			{
				free(rest);
				return (0);
			}
			continue ;
		}
		rest[counter++] = *table++;
	}
	rest[counter] = 0;
	return (rest);
}
