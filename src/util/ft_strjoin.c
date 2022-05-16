/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:53:58 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/16 20:48:55 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* joins two strings and frees s1,
return -1 if fail or 0 on success and assign new string to s1 variable */
int	ft_strjoin(char **s1, char const *s2)
{
	char	*res;
	char	*cur;
	char	*temp;

	if (!*s1 || !s2)
		return (ERROR);
	temp = *s1;
	res = malloc(ft_strlen(temp) + ft_strlen(s2) + 1);
	if (!res)
		return (ERROR);
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
