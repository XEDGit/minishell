/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:39 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/12 18:04:24 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n--)
	{
		s1++;
		s2++;
	}
	if (!n)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strexcmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n--)
	{
		s1++;
		s2++;
	}
	if (n <= 0 && !*s1)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 || !*s2)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
