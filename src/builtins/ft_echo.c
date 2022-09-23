/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:33:56 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:33:56 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <ft_printf.h>

int	ft_echo(char **args, t_env *env)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	if (args[1] && args[1][i++] == '-')
	{
		while (args[1][i] == 'n')
			i++;
		if (!args[1][i])
			start++;
	}
	i = 0;
	args = &args[start + 1];
	while (args && args[i])
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (!start)
		ft_printf("\n");
	return (0);
}
