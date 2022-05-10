/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/08 15:32:59 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 23:44:31 by lmuzio        ########   odam.nl         */
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

	if (delimiter == 1)
		delimiter = 0;
	c = 0;
	input = readline(">");
	if (!input)
		return (1);
	if (*input)
	{
		while (input[c] && ft_isspace(input[c]))
			c++;
		c = lexer_multiline_check(input + c, delimiter);
		if (c == ERROR)
			return (ERROR);
		*buffer = ft_strjoin(*buffer, input);
	}
	else if (!delimiter)
		c = 1;
	else
		c = delimiter;
	if (c)
		repeat_readline(buffer, c);
	free(input);
	return (0);
}

int	lexer(char *input)
{
	char	**tables;
	char	*repeat_buffer;
	int		count;

	count = 0;
	while (input[count] && ft_isspace(input[count]))
		count++;
	count = lexer_multiline_check(input + count, 0);
	if (count == ERROR)
		return (0);
	else
		repeat_buffer = ft_strdup(input);
	if (count)
	{
		count = repeat_readline(&repeat_buffer, count);
		if (count == ERROR)
			return (0);
		else if (count)
			return (1);
	}
	add_history(repeat_buffer);
	count = 0;
	tables = ft_split(repeat_buffer, "|&");
	while (tables[count])
		ft_printf("split: %s\n", tables[count++]);
	// parser(tables);
	free(repeat_buffer);
	free2d(tables, count);
	return (0);
}
