/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:53:46 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 22:13:27 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	srcsize;

	srcsize = ft_strlen(src);
	if (!dstsize)
		return (srcsize);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = 0;
	return (srcsize);
}
