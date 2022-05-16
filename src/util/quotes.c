/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:52:41 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/16 20:31:55 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_quotes(char *input)
{
	int		c;
	char	ch;
	char	*res;

	c = 0;
	ch = 0;
	res = ft_strdup(input);
	if (!res)
		return (0);
	while (res[c])
	{
		if (!ch && (res[c] == DOUBLE_QUOTE || res[c] == SINGLE_QUOTE))
		{
			ch = res[c];
			ft_strlcpy(res + c, res + c + 1, ft_strlen(res + c));
		}
		else if (ch && res[c] == ch)
		{
			ch = 0;
			ft_strlcpy(res + c, res + c + 1, ft_strlen(res + c));
		}
		else
			c++;
	}
	return (res);
}

int	skip_quotes(char *input)
{
	char	ch;
	char	*start;

	start = input;
	if (*input != DOUBLE_QUOTE && *input != SINGLE_QUOTE)
		return (0);
	ch = *input++;
	while (*input && *input != ch)
		input++;
	return (input - start);
}
