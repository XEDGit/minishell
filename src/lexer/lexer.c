/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/09 17:24:56 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(char *input)
{
	int	c;
	int	dist;

	while (*input && ft_isspace(*input))
		input++;
	if (*input == PIPE)
		return (ERROR);
	while (*input)
	{
		if (input[0] == PIPE && input[1] != PIPE)
		{
			dist = 0;
			c = 0;
			while (input[++c] && input[c] != PIPE)
				if (!ft_isspace(input[c]))
					dist++;
		}
		input++;
	}
	printf("pipe: %d	%d\n", c, dist);
	if (c && !dist)
		return (FALSE);
	return (TRUE);
}

// ' " |  << 
int	lexer_multiline_check(char *input)
{
	int	open;

	open = pipe_check(input);
	if (open)
		return (open);
	while (*input)
	{
		if (!open && *input == SINGLE_QUOTE)
			open = SINGLE_QUOTE;
		else if (!open && *input == DOUBLE_QUOTE)
			open = DOUBLE_QUOTE;
		else if (open == SINGLE_QUOTE && *input == SINGLE_QUOTE)
			open = 0;
		else if (open == DOUBLE_QUOTE && *input == DOUBLE_QUOTE)
			open = 0;
		input++;
	}
	if (open)
		return (open);
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
