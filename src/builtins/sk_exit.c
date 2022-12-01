/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:36:51 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/10/05 13:36:51 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	sk_exit(t_cmd *cmd)
{
	int		isdigit;

	isdigit = 0;
	if (cmd->args[1] && !cmd->args[2])
	{
		if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
			isdigit++;
		while (cmd->args[1][isdigit] && cmd->args[1][isdigit] <= '9' \
		&& cmd->args[1][isdigit] >= '0')
			isdigit++;
		if (cmd->args[1][isdigit])
			isdigit = 0;
		else
			g_exit_code = sk_atoi(cmd->args[1]);
		if (!isdigit)
			error_int("numeric argument required", "exit", 2, 0);
	}
	else if (cmd->args[1] && cmd->args[2])
		error_int("too many arguments", "exit", 1, 0);
	exit(g_exit_code);
}
