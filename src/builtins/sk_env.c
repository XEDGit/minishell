/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:17 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/01 18:04:35 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	ft_env(t_cmd *cmd, t_data *data)
{
	int		i;
	char	**envp;

	(void)cmd;
	i = 0;
	envp = data->env->envp->mem;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
