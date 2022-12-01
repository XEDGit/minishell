/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:33:56 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 17:25:46 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	check_flag(char *arg)
{
	int	n;

	n = 0;
	if (*arg == '-' && arg[1] == 'n')
		arg++;
	else
		return (false);
	while (arg[n] == 'n')
		n++;
	if (!arg[n])
		return (true);
	return (false);
}

int	sk_echo(t_cmd *cmd, t_data *data)
{
	bool	nl;
	int		i;

	i = 1;
	nl = true;
	(void)data;
	while (cmd->args && cmd->args[i] && check_flag(cmd->args[i]))
	{
		i++;
		nl = false;
	}
	while (cmd->args && cmd->args[i])
	{
		sk_printf("%s", cmd->args[i]);
		if (cmd->args[++i])
			sk_printf(" ");
	}
	if (nl)
		sk_printf("\n");
	return (0);
}
