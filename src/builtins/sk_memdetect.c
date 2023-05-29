#include <executer.h>

int	sk_memdetect(t_cmd *cmd, t_data *data)
{
	static bool	is_installed = false;
	if (is_installed)
		return (0);
	char 		*cmddup = sk_strdup(cmd->cmd);
	char		*tmp = check_paths(data->paths, cmddup);
	if (tmp)
	{
		is_installed = true;
		free(tmp);
	}
	else
	{
		error_int("Installing memdetect from github.com from git...", "memdetect-installer", 0, 0);
		if (sk_subshell("git clone 'https://github.com/xedgit/memdetect' memdetect.tmp && cd memdetect.tmp && CDOUT='cd ..' && chmod +x ./memdetect.sh && ./memdetect.sh --add-path; EX=$?; $CDOUT; rm -rf memdetect.tmp; exit $EX", data->env, data->aliases, 1, 0))
			return (error_int("Error while installing memdetect", "memdetect-installer", 1, 1));
		if (!g_exit_code)
		{
			error_int("Successfully installed memdetect, executing!", "memdetect-installer", 0, 0);
			is_installed = true;
		}
	}
	return (0);
}
