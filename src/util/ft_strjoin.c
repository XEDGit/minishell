/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 17:53:58 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 22:44:05 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// joins two strings and frees s1
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*cur;
	char	*temp;

	if (!s1 || !s2)
		return (0);
	temp = (char *)s1;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	cur = res;
	while (*s1)
		*cur++ = *s1++;
	while (*s2)
		*cur++ = *s2++;
	*cur = 0;
	free(temp);
	return (res);
}
