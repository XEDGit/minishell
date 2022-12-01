#include <executer.h>

int	ft_alias(t_cmd *cmd, t_data *data)
{
	int		i = 1;

	if (!cmd->args[1])
	{
		t_data	new = {0};
		new.env = data->aliases;
		return (ft_env(0, &new));
	}
	if (!strchr(cmd->args[1], '='))
	{
		char	*buff = env_get(data->aliases, cmd->args[1], 1);
		if (!buff || !*buff)
		{
			free(buff);
			return (error_int(0, 0, 1, true));
		}
		ft_printf("alias %s='%s'", cmd->args[1], buff);
		free(buff);
		return (false);
	}
	while (cmd->args[i])
		data->aliases = env_add(data->aliases, cmd->args[i++], 1);
	return (false);
}

int	check_aliases(t_cmd *cmd, t_env *aliases)
{
	char	*substitute;
	char	**substitutes;
	char	**new_args;
	int		oglen = 0;
	int		len = 0;

	if (!cmd->cmd)
		return (false);
	substitute = env_get(aliases, cmd->cmd, 1);
	if (!substitute || !*substitute)
	{
		free(substitute);
		return (false);
	}
	substitutes = ft_split(substitute, " ");
	free(substitute);
	if (!substitutes)
		return (error_int("malloc error", "alias", 1, 0));
	while (substitutes[len++]);
	while (cmd->args[oglen++]);
	new_args = malloc((len + oglen - 1) * sizeof(char *));
	if (!new_args)
		return (error_int("malloc error", "alias", 1, 0));
	len = -1;
	while (substitutes[++len])
		new_args[len] = substitutes[len];
	oglen = 0;
	while (cmd->args[++oglen])
		new_args[len++] = cmd->args[oglen];
	new_args[len] = 0;
	free(cmd->cmd);
	free(cmd->args);
	free(substitutes);
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
	return (true);
}

