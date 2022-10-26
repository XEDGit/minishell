/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:34:27 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 16:17:59 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	ft_pwd(char **args, t_env *env)
{
	char	*pwd;

	pwd = env_get(env, "PWD", 1);
	if (!pwd)
		return (error_int("memory error", "pwd", 1, 1));
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
