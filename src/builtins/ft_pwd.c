/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:27 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:34:27 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <stdlib.h>
#include <ft_printf.h>

int	ft_pwd(char **args, t_env *env)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (1);// TODO error
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
