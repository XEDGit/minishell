/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:53:46 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 22:12:40 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strclen(const char *start, const char *end)
{
	int			cont;
	const char	*temp;

	cont = 0;
	temp = end;
	while (*end)
		if (*start == *end++)
			cont++;
	if (cont)
		start++;
	while (*start)
	{
		end = temp;
		while (*end)
			if (*start == *end++)
				return (cont);
		cont++;
		start++;
	}
	return (cont);
}

size_t	ft_strlen(const char *str)
{
	const char	*temp;

	if (!str)
		return (0);
	temp = str;
	while (*str)
		str++;
	return (str - temp);
}
