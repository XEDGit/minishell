/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:44 by lmuzio            #+#    #+#             */
/*   Updated: 2022/01/18 17:58:07 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_word(const char *s, const char *word, int len)
{
	while (*word && *s == *word && len--)
	{
		word++;
		s++;
	}
	if (!*word && len >= 0)
		return (1);
	return (0);
}

char	*sk_strnstr(const char *haystack, const char *needle, unsigned int len)
{
	if (!*needle || haystack == needle)
		return ((char *)haystack);
	while (len && *haystack)
	{
		if (*haystack == *needle)
			if (check_word(haystack, needle, len))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
