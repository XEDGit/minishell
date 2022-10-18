/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checks2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 18:33:40 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 01:22:25 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	semicolon_check(char *input)
{
	while (*input)
	{
		if (*input == ';')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == ';')
				return (ERROR);
			else
				input++;
		}
		if (*input)
			input++;
	}
	return (false);
}

char	*find_next_char(char *start)
{
	start++;
	while (*start && *start == ' ')
		start++;
	return (start);
}

int	io_routine(char *input, char ch)
{
	char	ch2;

	ch2 = '<';
	if (ch == '<')
		ch2 = '>';
	if ((*++input == ch && *++input == ch) || *input == ch2)
		return (true);
	if (*input == ch)
		input++;
	while (*input && *input == ' ')
		input++;
	if (*input == ch || *input == ch2)
		return (true);
	return (false);
}

int	io_check(char *input)
{
	while (*input)
	{
		if (*input == '<' && io_routine(input, '<'))
			return ('<');
		else if (*input == '>' && io_routine(input, '>'))
			return ('>');
		input++;
	}
	return (false);
}
