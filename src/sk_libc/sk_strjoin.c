/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 17:53:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/04 01:20:50 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

/* Joins two strings and frees s1,
return -1 and free s2 on fail, return 0 on success
and assign new string to s1 variable */
int	sk_strjoin(char **s1, char const *s2, int free_s2)
{
	char	*res;
	char	*cur;
	char	*temp;

	if (!s2)
		return (false);
	if (!*s1)
	{
		temp = sk_strdup(s2);
		if (!temp)
			return (ERROR);
		*s1 = temp;
		return (false);
	}
	temp = *s1;
	res = malloc(sk_strlen(temp) + sk_strlen(s2) + 1);
	if (!res)
	{
		if (free_s2)
			free((void *)s2);
		return (ERROR);
	}
	cur = res;
	while (*temp)
		*cur++ = *temp++;
	while (*s2)
		*cur++ = *s2++;
	*cur = 0;
	free(*s1);
	*s1 = res;
	return (false);
}
