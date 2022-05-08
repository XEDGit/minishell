/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/08 19:54:53 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(char *input)
{
	int	c;
	int	dist;

	while (*input)
	{
		if (input[0] == PIPE && input[1] != PIPE)
		{
			dist = 0;
			c = 0;
			while (input[c] && input[c + 1] != PIPE)
				if (!ft_isspace(input[c++]))
					dist++;
		}
		else if (input[0] == PIPE && input[1] == PIPE)
			input++;
		input++;
	}
	printf("pipe: %d	%d\n", c, dist);
	if (c && dist == 1)
		return (FALSE);
	return (TRUE);
}

// ' " |  <<
int	lexer_multiline_check(char *input)
{
	int	single_quotes;
	int	double_quotes;

	double_quotes = 0;
	single_quotes = 0;
	if (pipe_check(input))
		return (PIPE);
	while (*input)
	{
		if (!single_quotes && !double_quotes && *input == SINGLE_QUOTE)
			single_quotes++;
		else if (!double_quotes && !single_quotes && *input == DOUBLE_QUOTE)
			double_quotes++;
		else if (single_quotes && *input == SINGLE_QUOTE)
			single_quotes--;
		else if (double_quotes && *input == DOUBLE_QUOTE)
			double_quotes--;
		input++;
	}
	if (single_quotes)
		return (SINGLE_QUOTE);
	if (double_quotes)
		return (DOUBLE_QUOTE);
	return (TRUE);
}

int	lexer(char *input)
{
	char	**buffer;
	int		count;

	ft_printf("check:%d\n", lexer_multiline_check(input));
	count = -1;
	buffer = ft_split(input, "|&");
	while (buffer[++count])
		printf("split[%d]: %s\n", count, buffer[count]);
	free2d(buffer, count);
	return (0);
}
