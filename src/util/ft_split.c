/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:54:14 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/04 18:53:56 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include <libc.h>

size_t	word_count(const char *s, char c)
{
	int	cont;

	cont = 0;
	if (!*s)
		return (1);
	if (*s != c)
		cont++;
	while (*s)
	{
		if (*s++ == c && *s != c)
		{
			cont++;
			while (*s == c && *s)
				s++;
		}
	}
	if (*(s - sizeof(char)) == c)
		cont--;
	return (cont);
}

char	**free2d(char **tofree, int len)
{
	while (len--)
		free(tofree[len]);
	free(tofree);
	return (0);
}

size_t	ft_strclen(const char *start, const char end)
{
	int	cont;

	cont = 0;
	if (*start == end)
	{
		start++;
		cont++;
	}
	while (*start != end && *start++)
		cont++;
	return (cont);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	srcsize;

	srcsize = ft_strclen(src, 0);
	if (!dstsize)
		return (srcsize);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = 0;
	return (srcsize);
}

char	**ft_split(char const *s, char c)
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
		if (*s == c)
			s++;
		cont = ft_strclen(s, c);
		if (!cont && *s)
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

#include <stdio.h>
int main()
{
	char **s;
	int	c = 0;

	s = ft_split("arg || ( arg || echo sos && arg ) | echo a  || echo lol", '|');
	while (s[c])
		printf("%s\n", s[c++]);
	free2d(s, c);
}