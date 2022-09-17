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
	char	**envp;

	envp = env->envp->mem;
	while (envp && *envp && ft_strchr(*envp, '='))
		ft_printf("%s\n", *envp++);
	return (0);
}
