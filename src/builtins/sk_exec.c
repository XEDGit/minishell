#include <shared.h>
char	*check_paths(char **paths, char *cmd);

int sk_exec(t_cmd *cmd, t_data *data)
{
	char    **args;
	int		clean = 0, dash = 0, name = 0;
	char	*prog, *dash_buf, *name_buf;
	char    *flags[4] = {
		"-c",
		"-l",
		"-a",
		0
	};
	int		i;

	args = cmd->args;
	if (!*(args++))
		return (0);
	while (*args && **args == '-')
	{
		i = 0;
		while (flags[i])
		{
			if (!sk_strcmp(*args, flags[i]))
			{
				if (!i)
					clean++;
				else if (i == 1)
					dash++;
				else
				{
					name++;
					args++;
					name_buf = args[0];
				}
				break ;
			}
			i++;
		}
		args++;
	}
	if (!*args)
		return (0);
	if (clean)
	{
		env_free(data->env);
		data->env = env_create((char **){0});
	}
	args[0] = check_paths(data->paths, args[0]);
	if (!args[0])
		return (127);
	prog = sk_strdup(args[0]);
	if (name)
	{
		free(args[0]);
		args[0] = name_buf;
	}
	if (dash)
	{
		dash_buf = malloc(sizeof(char) * 2);
		if (!dash_buf)
			return (error_int("malloc fail", "exec", -1, 1));
		dash_buf[0] = '-';
		dash_buf[1] = 0;
		if (sk_strjoin(&dash_buf, args[0], false))
		{
			free(dash_buf);
			return (error_int("malloc fail", "exec", -1, 1));
		}
		free(args[0]);
		args[0] = dash_buf;
	}
	execve(prog, args, data->env->envp->mem);
	return (1);
}