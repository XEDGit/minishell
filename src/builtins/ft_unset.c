/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:31 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/02 18:15:30 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	ft_unset(char **args, t_env *env)
{
	int	ret;

	ret = 0;
	while (++args && *args)
	{
		if (!valid_varname(*args))
		{
			error_int(VARIDERR, "unset", 1, 0);
			ret = 1;
			continue ;
		}
		env_remove(env, *args, 0);
	}
	return (ret);
}
