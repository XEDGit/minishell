#include <shared.h>

int subshell(char *input, t_env *env, int tofork)
{
    pid_t   child;

    child = 0;
    if (tofork)
    {
        child = fork();
        if (child == -1)
            return (error_int("Error forking process", "subshell", -1, true));
    }
    if (!child)
    {
        lexer(input, env);
        env_free(env);
        exit(g_exit_code);
    }
    if (tofork)
        watch_child(child);
    return (false);
}

int	parse_argv(char **argv, t_env *env)
{
	int		i;
	int		i_flags;
    int     (*funcs[2])(char *, t_env *, int) = {
        &subshell,
        0
    };
	char	*flags[2] = {
		"-c",
		0
	};

	i = 0;
	i_flags = 0;
	while (argv[i])
	{
		while (flags[i_flags])
			if (!strcmp(argv[i], flags[i_flags++]))
            {
                if (!argv[i + 1])
                    exit(error_int("Missing argument", argv[i], 1, true));
				funcs[i_flags - 1](argv[i + 1], env, false);
                return (true);
            }
		i_flags = 0;
		i++;
	}
	return (false);
}
