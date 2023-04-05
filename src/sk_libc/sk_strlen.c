/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:53:46 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/04 20:46:44 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		skip_quotes(char *input);

size_t	sk_strclen(const char *start, const char *end)
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

size_t	sk_strclen_no_quotes(const char *start, const char *end)
{
	int			cont;
	const char	*temp;
	int			i;

	cont = 0;
	temp = end;
	if (*start == '|' || *start == '&')
	{
		cont++;
		start++;
	}
	while (*start)
	{
		end = temp;
		i = 0;
		if (start[i] == '(')
			while (start[i] && start[i] != ')')
				i++;
		if (start[i] == '"')
			while (start[i] && start[i] != '"')
				i++;
		start += i;
		cont += i;
		while (*end)
			if (*start == *end++)
				return (cont);
		cont++;
		start++;
	}
	return (cont);
}

size_t	sk_strlen(const char *str)
{
	const char	*temp;

	if (!str)
		return (0);
	temp = str;
	while (*str)
		str++;
	return (str - temp);
}
