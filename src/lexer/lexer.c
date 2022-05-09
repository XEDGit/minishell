/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/09 19:37:04 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(char *input)
{
	int	c;
	int	dist;

	if ((input[0] == PIPE && input[1] != PIPE) || \
		(input[0] == AMP && input[1] != AMP))
	{
		dist = 0;
		c = 0;
		while (input[++c] && input[c] != PIPE && input[c] != AMP)
			if (!ft_isspace(input[c]))
				dist++;
	}
	if (!input[c] && !dist)
		return (FALSE);
	if (c && !dist)
		return (ERROR);
	return (TRUE);
}

// ' " |  << 
int	lexer_multiline_check(char *input)
{
	int	open;

	if (*input == PIPE || *input == AMP)
		return (ERROR);
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
		else if (!open && (*input == PIPE || *input == AMP))
			if (pipe_check(input))
				return (pipe_check(input));
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

	while (*input && ft_isspace(*input))
		input++;
	ft_printf("check:%d\n", (count = lexer_multiline_check(input)));
	if (count == ERROR)
		return (0);
	count = -1;
	buffer = ft_split(input, "|&");
	while (buffer[++count])
		printf("split[%d]: %s\n", count, buffer[count]);
	free2d(buffer, count);
	return (0);
}
