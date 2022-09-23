#include <shared.h>

int	ft_exit(t_cmd *cmd)
{
	int	len;
	int	isdigit;

	len = 18;
	isdigit = 0;
	if (cmd->args[1] && !cmd->args[2])
	{
		if (cmd->args[1][0] == '-')
		{
			isdigit++;
			len++;
		}
		while (cmd->args[1][isdigit] && cmd->args[1][isdigit] <= '9' && cmd->args[1][isdigit] >= '0')
			isdigit++;
		if (cmd->args[1][isdigit])
			isdigit = 0;
		g_exit_code = ft_atoi(cmd->args[1]);
		if (ft_strlen(cmd->args[1]) > len || !isdigit)
			error_int("numeric argument required", "exit", 2, 0);
	}
	else if (cmd->args[1] && cmd->args[2])
		error_int("too many arguments", "exit", 1, 0);
	exit(g_exit_code);
}