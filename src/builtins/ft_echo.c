/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:33:56 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/01 18:05:03 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <ft_printf.h>
#include <stdbool.h>

int	check_flag(char *arg)
{
	int	n;

	n = 0;
	if (*arg == '-')
		arg++;
	else
		return (false);
	while (arg[n] == 'n')
		n++;
	if (!arg[n])
		return (true);
	return (false);
}

int	ft_echo(char **args, t_env *env)
{
	bool	nl;
	int		i;

	i = 1;
	nl = true;
	(void)env;
	while (args && args[i] && check_flag(args[i]))
	{
		i++;
		nl = false;
	}
	while (args && args[i])
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
	return (0);
}
