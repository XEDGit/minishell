#include <shared.h>

int	parse_argv(char **argv, t_env *env, t_env *aliases)
{
	int		i;
	int		i_flags;
    int     (*arg_funcs[2])(char *, t_env *, t_env *, int, int) = {
        &sk_subshell,
        0
    };
	char	*arg_flags[2] = {
		"-c",
		0
	};
	char	*noarg_flags[2] = {
		"-v",
		0
	};

	i = 1;
	while (argv[i])
	{
		i_flags = 0;
		while (arg_flags[i_flags])
			if (!strcmp(argv[i], arg_flags[i_flags++]))
            {
                if (!argv[i + 1])
                    exit(error_int("missing argument", argv[i], 1, true));
				arg_funcs[i_flags - 1](argv[i + 1], env, aliases, false, 0);
                return (true);
            }
		i_flags = 0;
		while (noarg_flags[i_flags])
			if (!strcmp(argv[i], noarg_flags[i_flags++]))
			{
				switch (i_flags - 1)
				{
					case 0:
						env->opts = add_var(env->opts, sk_strdup("VERBOSE=1"), buff_contains(env->opts, "VERBOSE", 0));
						break;
					default:
						break;
				}
				return (true);
			}
		i++;
	}
	return (false);
}
