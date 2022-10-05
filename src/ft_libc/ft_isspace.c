/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 17:56:47 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/10/05 13:38:51 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int str)
{
	if (str == ' ' || str == '	' || str == '\t'\
	|| str == '\n' || str == '\v' || str == '\f' || str == '\r')
		return (1);
	return (0);
}

int	ft_strisspace(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (1);
	return (0);
}
