/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/08 15:32:59 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 05:18:56 by lmuzio        ########   odam.nl         */
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
		if (!input[c] && !dist)
			return (FALSE);
	}
	if (c && !dist)
		return (ERROR);
	return (TRUE);
}

// don't forget <<
int	lexer_multiline_check(char *input, int delimiter)
{
	int	open;

	while (*input && ft_isspace(*input))
		input++;
	open = delimiter;
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

int	repeat_readline(char **buffer, char delimiter)
{
	char	*input;
	int		c;

	input = readline(">");
	if (!input)
		return (ERROR);
	if (*input)
	{
		if (delimiter == 1)
			delimiter = 0;
		c = lexer_multiline_check(input, delimiter);
		if (c == ERROR)
		{
			free(input);
			return (1);
		}
		*buffer = ft_strjoin(*buffer, input);
	}
	else
		c = delimiter;
	if (c)
		c = repeat_readline(buffer, c);
	free(input);
	return (c);
}

int	lexer(char *input)
{
	char	**tables;
	char	*repeat_buffer;
	int		count;

	count = lexer_multiline_check(input, 0);
	if (count == ERROR)
		return (1);
	else
		repeat_buffer = ft_strdup(input);
	if (count)
		count = repeat_readline(&repeat_buffer, count);
	if (count)
	{
		free(repeat_buffer);
		return (count);
	}
	add_history(repeat_buffer);
	tables = ft_split(repeat_buffer, "|&");
	parser(tables);
	free(repeat_buffer);
	free2d(tables, 0);
	return (0);
}
