/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:27 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/01 18:05:39 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	ft_pwd(char **args, t_env *env)
{
	char	*pwd;

	(void)args;
	(void)env;
	pwd = getcwd(0, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
