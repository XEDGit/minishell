/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 18:52:41 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/06/08 22:10:52 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//	return true if inside unclosed quotes
int	is_open(char c)
{
	static int	open;

	if (!open && c == SINGLE_QUOTE)
		open = SINGLE_QUOTE;
	else if (!open && c == DOUBLE_QUOTE)
		open = DOUBLE_QUOTE;
	else if (open == SINGLE_QUOTE && c == SINGLE_QUOTE)
		open = 0;
	else if (open == DOUBLE_QUOTE && c == DOUBLE_QUOTE)
		open = 0;
	return (open);
}

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
	return (input - start + 1);
}
