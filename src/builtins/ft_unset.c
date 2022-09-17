/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:31 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:34:31 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

int	ft_unset(char **args, t_env *env)
{
	while (++args && *args)
		env_remove(env, *args, 0);
	return (0);
}
