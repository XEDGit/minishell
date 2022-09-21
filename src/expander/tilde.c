#include <parser.h>

static size_t	tilde_count(char *table)
{
	size_t	i;
	int		open;

	i = 0;
	while (*table)
	{
		open = is_open(*table);
		if (!open && *table == '~')
			i++;
		table++;
	}
	return (i);
}

char	*copy_tilde_table(char *new, char *table, char *home, size_t size)
{
	size_t	c;
	size_t	i;
	int		open;
	size_t	home_len;

	i = 0;
	c = 0;
	home_len = ft_strlen(home);
	while (table[i])
	{
		open = is_open(table[i]);
		if (!open && table[i] == '~')
		{
			// ft_printf("ciao\n");
			ft_strlcpy(new + c, home, size);
			i++;
			c += home_len;
			continue ;
		}
		new[c++] = table[i++];
	}
	new[c] = 0;
	return (new);
}

char	*ft_tilde_expand(char **table, t_env *env)
{
	
	char	*home;
	size_t	size;
	char	*new_table;

	home = env_get(env, "HOME", 1);
	if (!home)
		return (0);
	size = tilde_count(*table) * ft_strlen(home);
	if (!size)
	{
		free(home);
		return (*table);
	}
	size += ft_strlen(*table);
	new_table = malloc(sizeof(char) * size);
	if (!new_table)
	{
		free(home);
		return (0);
	}
	copy_tilde_table(new_table, *table, home, size);
	free(*table);
	*table = new_table;
	return (new_table);
}
