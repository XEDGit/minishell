#include <parser.h>

char	*clean_quotes(char *table)
{
	int	i;
	int	open;

	i = 0;
	while (*table)
	{
		open = is_open(*table);
		if ((!open && (*table == '\'' || *table == '\"')) || \
		(open && *table == open))
			*table = ' ';
		table++;
	}
	
	return table;
}

//	Correct order:
//	- tilde expansion
//	- variable expansion
//	- * pattern
//	- unquoted ' " removed
int	expander(char **tables, t_env *env)
{
	int	i;

	i = 0;
	while (tables[i])
	{
		if (!ft_tilde_expand(&tables[i], env) || !vars_expansion(&tables[i], env))
			return (false);
		// wildcard TODO
		clean_quotes(tables[i]);
		i++;
	}
	return (true);
}
