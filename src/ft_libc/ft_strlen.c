/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:53:46 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/06/08 22:17:17 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		skip_quotes(char *input);

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

size_t	ft_strclen_no_quotes(const char *start, const char *end)
{
	int			cont;
	const char	*temp;

	cont = 0;
	temp = end;
	cont += skip_quotes((char *)start);
	start += skip_quotes((char *)start);
	while (*end)
		if (*start == *end++)
			cont++;
	if (cont && *start)
		start++;
	while (*start)
	{
		end = temp;
		cont += skip_quotes((char *)start);
		start += skip_quotes((char *)start);
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
