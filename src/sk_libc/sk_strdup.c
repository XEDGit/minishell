/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 22:51:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 22:53:39 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	sk_strlen(const char *str);

char	*sk_strdup(const char *s1)
{
	char	*dup;
	char	*cur;

	dup = malloc(sk_strlen(s1) + 1);
	if (!dup)
		return (0);
	cur = dup;
	while (*s1)
		*cur++ = *s1++;
	*cur = 0;
	return (dup);
}
