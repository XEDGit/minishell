/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:54:14 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/03 00:10:53 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include <libc.h>

size_t	word_count(char *s, char *c)
{
	int		cont;
	int		first_word;
	int		last_word;
	char	*temps;

	cont = 0;
	while (*c)
	{
		temps = s;
		if (*temps != *c)
			first_word = 1;
		while (*temps)
		{
			if (*temps++ == *c && *temps != *c)
			{
				cont++;
				while (*temps == *c && *temps)
					temps++;
			}
		}
		// if (*(temps - sizeof(char)) == *c)
		// 	last_word = 1;
		c++;
	}
	return (cont + first_word);
}

int main(){
	printf("%zu, %zu, %zu, %zu", word_count("ebghye", "ekr"), word_count(" e e", "ekr"), word_count("e e ", "ekr"), word_count(" e e ", "ekr"));
}

char	**free2d(char **tofree, int len)
{
	while (len-- && tofree[len])
		free(tofree[len]);
	free(tofree);
	return (0);
}

size_t	ft_strclen(char *start, char *end)
{
	int	result;
	int	cont;

	result = INT32_MAX;
	while (*end)
	{
		cont = 0;
		if (*start == *end)
		{
			start++;
			cont++;
		}
		while (*start != *end && *start++)
			cont++;
		if (cont < result)
			result = cont;
		end++;
	}
	return (result);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
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

char	**ft_split(char *s, char *c)
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
		cont = ft_strclen(s, c);
		if (!cont)
		{
			s++;
			continue ;
		}
		res[resc] = malloc(cont + 1);
		if (!res[resc])
			return (free2d(res, resc + 1));
		ft_strlcpy(res[resc++], s, cont + 1);
		s += cont;
	}
	res[resc] = 0;
	return (res);
}
