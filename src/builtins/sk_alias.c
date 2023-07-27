#include <executer.h>

int	sk_alias(t_cmd *cmd, t_data *data)
{
	int		i = 1;

	if (!cmd->args[1])
	{
		t_data	new = {0};
		new.env = data->aliases;
		return (sk_env(0, &new));
	}
	if (!strchr(cmd->args[1], '='))
	{
		char	*buff = env_get(data->aliases, cmd->args[1], 1);
		if (!buff || !*buff)
		{
			free(buff);
			return (error_int(0, 0, 1, true));
		}
		sk_printf("alias %s='%s'", cmd->args[1], buff);
		free(buff);
		return (false);
	}
	while (cmd->args[i])
		data->aliases = env_add(data->aliases, cmd->args[i++], 1);
	return (false);
}

void	erase_chars(char *str, char *chars)
{
	int i = 0, offset = 0, target = 0;
	while (str[i])
	{
		int j = 0;
		if (str[i] == '(')
			while (str[i++] != ')')
				;
		while (chars[j])
			if (str[i] == chars[j++])
			{
				target = chars[j - 1];
				offset++;
				while (str[++i] != target)
					str[i - offset] = str[i];
				i++;
				offset++;
				break ;
			}
		j = 0;
		if (target)
		{
			target = 0;
			continue ;
		}
		if (!str[i])
			break ;
		str[i - offset] = str[i];
		i++;
	}
	str[i - offset] = 0;
}

char	**adjust_args(char **substitutes, t_cmd *cmd)
{
	int		oglen = 0;
	int		len = 0;
	char	**new_args;

	while (substitutes[len++]);
	while (cmd->args[oglen++]);
	new_args = malloc((len + oglen - 1) * sizeof(char *));
	if (!new_args)
		return ((char **)(long)error_int("malloc fail", cmd->cmd, 1, 0));
	len = -1;
	while (substitutes[++len])
	{
		erase_chars(substitutes[len], "\"\'");
		new_args[len] = substitutes[len];
	}
	oglen = 0;
	while (cmd->args[++oglen])
		new_args[len++] = cmd->args[oglen];
	new_args[len] = 0;
	return (new_args);
}

int	check_aliases(t_cmd *cmd, t_env *aliases)
{
	char	*substitute;
	char	**substitutes;
	char	**new_args;

	if (!cmd->cmd)
		return (false);
	substitute = env_get(aliases, cmd->cmd, 1);
	if (!substitute || !*substitute)
	{
		free(substitute);
		return (false);
	}
	substitutes = sk_split(substitute, " ");
	free(substitute);
	if (!substitutes)
		return (error_int("malloc fail", "alias", 1, 0));
	new_args = adjust_args(substitutes, cmd);
	if (!new_args)
	{
		free2d(substitutes, 0);
		return (ERROR);
	}
	free(cmd->cmd);
	free(cmd->args);
	free(substitutes);
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
	return (false);
}

