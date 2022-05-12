/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 17:54:14 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 04:53:39 by lmuzio        ########   odam.nl         */
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

int	free2dint(int **tofree, int len)
{
	if (!len)
		while (tofree[len])
			len++;
	while (len--)
		free(tofree[len]);
	free(tofree);
	return (1);
}

int	free2d(char **tofree, int len)
{
	if (!len)
		while (tofree[len])
			len++;
	while (len--)
		free(tofree[len]);
	free(tofree);
	return (1);
}

int	copy_word(const char *s, char **res, int resc, int cont)
{
	res[resc] = malloc(cont + 1);
	if (!res[resc])
		return (free2d(res, resc + 1));
	ft_strlcpy(res[resc], s, cont + 1);
	return (0);
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
		cont = 0;
		while (c[cont])
			if (c[cont++] == *s)
				s++;
		cont = ft_strclen(s, c);
		if (!cont)
			continue ;
		if (copy_word(s, res, resc++, cont))
			return (0);
		s += cont;
	}
	res[resc] = 0;
	return (res);
}
