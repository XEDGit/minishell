/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:17 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:34:17 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	ft_env(char **args, t_env *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = env->envp->mem;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
