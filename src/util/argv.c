#include <shared.h>

int	parse_argv(char **argv, t_env *env, t_env *aliases)
{
	int		i;
	int		i_flags;
    int     (*funcs[2])(char *, t_env *, t_env *, int, int) = {
        &sk_subshell,
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
                    exit(error_int("missing argument", argv[i], 1, true));
				funcs[i_flags - 1](argv[i + 1], env, aliases, false, 0);
                return (true);
            }
		i_flags = 0;
		i++;
	}
	return (false);
}
