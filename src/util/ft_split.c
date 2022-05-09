/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:54:14 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/09 16:43:02 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	word_count(const char *s, char *c)
{
	int			cont;
	const char	*start;
	char		*temp;

	cont = 0;
	start = s;
	if (!*s)
		return (0);
	while (*s)
	{
		temp = c;
		while (*temp)
		{
			if (*temp == *s && s != start)
			{
				if (*(s + 1))
					cont++;
				if (*(s + 1) && *temp == *(s + 1))
					s++;
			}
			temp++;
		}
		s++;
	}
	return (cont + 1);
}

char	**free2d(char **tofree, int len)
{
	while (len--)
		free(tofree[len]);
	free(tofree);
	return (0);
}

size_t	ft_strclen(const char *start, const char *end)
{
	int			cont;
	const char	*temp;

	cont = 0;
	temp = end;
	while (*end)
	{
		if (*start == *end++)
		{
			start++;
			cont++;
		}
	}
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	srcsize;

	srcsize = ft_strclen(src, "\0");
	if (!dstsize)
		return (srcsize);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = 0;
	return (srcsize);
}

char	**ft_split(char const *s, char *c)
{
	char	**res;
	int		cont;
	int		resc;

	resc = 0;
	if (!s)
		return (0);
	res = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (*s)
	{
		if (*s == c[0] || *s == c[1])
			s++;
		cont = ft_strclen(s, c);
		if (!cont)
			continue ;
		res[resc] = malloc(cont + 1);
		if (!res[resc])
			return (free2d(res, resc + 1));
		ft_strlcpy(res[resc++], s, cont + 1);
		s += cont;
	}
	res[resc] = 0;
	return (res);
}
