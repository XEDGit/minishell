#include <shared.h>
#include <dirent.h>

int count_items(char *path)
{
	struct dirent	*dir;
	DIR				*d;
	int				items = 0;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type != DT_REG)
				continue ;
			items++;
		}
		closedir(d);
	}
	return (items);
}

char	**completions_generator(t_env *newenv)
{
	static t_env	*env;
	char			**completions, *path, **paths;
	struct dirent	*dir;
	DIR				*d;
	int				path_i, comp_i = 0, total;

	if (newenv && (env = newenv))
		return (0);
	if (!env)
		return (0);
	total = 0;
	path = env_get(env, "PATH", 1);
	// count items in path
	if (path && *path)
	{
		paths = sk_split(path, ":");
		free(path);
		path = (char *)0x1;
		if (!paths)
			return ((char **)(long)error_int("malloc error", "autocomplete", -1, 0));
		path_i = 0;
		while (paths[path_i])
			total += count_items(paths[path_i++]);
	}
	else if (path && !*path)
	{
		free(path);
		path = 0;
	}
	// allocate completions
	completions = malloc(sizeof(char *) * (total + 1));
	if (!completions)
		return ((char **)(long)error_int("malloc error", "autocomplete", -1, 0));
	// fill in completions from path
	if (path)
	{
		path_i = 0;
		while (paths[path_i])
		{
			d = opendir(paths[path_i]);
			if (d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					if (dir->d_type != DT_REG)
						continue;
					completions[comp_i] = sk_strdup(dir->d_name);
					if (!completions[comp_i++])
					{
						free2d(completions, 0);
						completions = 0;
						return ((char **)(long)error_int("malloc error", "autocomplete", -1, 0));
					}
				}
				closedir(d);
			}
			path_i++;
		}
		free2d(paths, 0);
	}
	completions[comp_i] = 0;
	return (completions);
}

char *match_completion(const char *text, int state)
{
	static int	i, len;
	char		*completion = 0;
	static char	**completions = 0;

	if (state == -1)
	{
		if (completions)
			free2d(completions, 0);
		completions = 0;
		return (0);
	}
	if (completions == 0)
		completions = completions_generator(0);
	if (!state)
	{
		i = 0;
		len = sk_strlen(text);
	}
	if (!completions)
		return (0);
	while (completions[i])
	{
		if (*text == *completions[i] && !sk_strncmp(completions[i], text, len))
		{
			completion = sk_strdup(completions[i]);
			i++;
			return (completion);
		}
		i++;
	}
	return (0);
}

char **completion(const char *text, int start, int end)
{
	(void)start;
	(void)end;
	return (rl_completion_matches(text, match_completion));
}
