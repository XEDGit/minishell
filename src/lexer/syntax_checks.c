/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/08 15:32:59 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 15:28:20 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	dchar_check(char *input, char ch)
{
	while (*input)
	{
		if (*input == ch)
		{
			input++;
			if (*input != ch)
				return (ERROR);
			else
				input++;
		}
		if (*input)
			input++;
	}
	return (false);
}

int	pipe_check(char *input)
{
	int	c;
	int	dist;

	c = 0;
	dist = 0;
	if ((input[0] == PIPE && input[1] == PIPE && input[2] == PIPE) || \
		(input[0] == AMP && input[1] == AMP && input[2] == AMP))
		return (ERROR);
	if ((input[0] == PIPE && input[1] != PIPE) || \
		(input[0] == AMP && input[1] != AMP))
	{
		while (input[++c] && input[c] != PIPE && input[c] != AMP)
			if (!ft_isspace(input[c]))
				dist++;
		if (!input[c] && !dist)
			return (true);
	}
	if (c && !dist)
		return (ERROR);
	return (false);
}

int	check_quotes(char *in, int *open, int delimiter)
{
	if (!*open && *in == SINGLE_QUOTE)
		*open = SINGLE_QUOTE;
	else if (!*open && *in == DOUBLE_QUOTE)
		*open = DOUBLE_QUOTE;
	else if (*open == SINGLE_QUOTE && *in == SINGLE_QUOTE)
		*open = 0;
	else if (*open == DOUBLE_QUOTE && *in == DOUBLE_QUOTE)
		*open = 0;
	else if (!*open && !delimiter && (*in == PIPE || *in == AMP))
		if (pipe_check(in))
			return (pipe_check(in));
	return (0);
}

int	lexer_multiline_check(char *in, int delimiter)
{
	int	open;
	int	err;

	open = delimiter;
	while (*in && *in == ' ')
		in++;
	if (!delimiter && (*in == PIPE || *in == AMP || dchar_check(in, AMP)))
		return (ERROR);
	while (*in)
	{
		err = check_quotes(in, &open, delimiter);
		if (err)
			return (err);
		in++;
	}
	if (open)
		return (open);
	return (false);
}

int	parenthesis_check(char *input)
{
	int	depth;
	int	c;

	c = 0;
	depth = 0;
	while (input[c])
	{
		if (input[c] == '(')
		{
			if (check_double_commands(input, c, -1) || \
			*find_next_char(input + c) == ')')
				return (error_int("Error parsing syntax near '('", 0, 258, 1));
			depth++;
		}
		else if (input[c] == ')' && (--depth == -1 || \
				check_double_commands(input, c, 1)))
			return (error_int("Error parsing syntax near ')'", 0, 258, 1));
		c++;
	}
	if (depth)
		return (true);
	return (false);
}
