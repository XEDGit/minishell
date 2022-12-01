/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/15 15:25:13 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	repeat_readline(char **buffer, char delimiter, t_data *data)
{
	char	*input;
	int		c;

	input = readline(">");
	if (input && *input)
	{
		c = lexer_multiline_check(input, delimiter);
		if (c == ERROR)
		{
			free(input);
			return (error_int("syntax error", 0, 2, 1));
		}
		if (delimiter != 1 && sk_strjoin(buffer, "\n", false) == ERROR)
			return (error_int("malloc error", 0, -1, ERROR));
		if (sk_strjoin(buffer, input, true) == ERROR)
			return (error_int("malloc error", 0, -1, ERROR));
	}
	else if (input)
		c = delimiter;
	else
		c = error_int("syntax error", 0, 2, ERROR);
	free(input);
	if (c > 0)
		c = repeat_readline(buffer, c, data);
	return (c);
}

int	syntax_check(char *input, t_data *data)
{
	int	error;

	if (!check_standalone_redirects(input))
		return (error_int("syntax error", 0, 2, 1));
	if (parenthesis_check(data->input))
		return (error_int("syntax error near ')'", 0, 2, 1));
	error = io_check(input);
	if (error)
	{
		sk_dprintf(2, "SkiruSh: Parsing failed at char '%c'\n", error);
		g_exit_code = 2;
		return (true);
	}
	return (false);
}

int	lexer_semicolon(char *input, t_data *data)
{
	char	**tables;
	int		code;

	if (syntax_check(input, data))
		return (1);
	code = 0;
	tables = sk_split(input, "|&");
	if (tables)
		code = parser(tables, data);
	else
		error_int("Allocation failed", "malloc", -1, 0);
	if (code == ERROR || code == 2)
		return (code);
	waitpid(-1, 0, 0);
	return (0);
}

int	lexer(char *input, t_env *env, t_env *aliases)
{
	char			**semicolon;
	int				count;
	int				code;
	t_data			data;

	data = (t_data){0, 0, 0, 0, 0, env, aliases};
	count = lexer_multiline_check(input, 0);
	if (count == ERROR)
	{
		add_history(input);
		return (error_int("Syntax error", 0, 2, 1));
	}
	if (multiline_handle(&data, input, count))
		return (1);
	semicolon = sk_split(data.input, ";");
	if (!semicolon)
		error_int("Allocation failed", "malloc", -1, 0);
	count = 0;
	code = 0;
	while (semicolon && semicolon[count] && code == 0)
		code = lexer_semicolon(semicolon[count++], &data);
	free(data.input);
	free2d(semicolon, 0);
	free2dint(data.heredocs, 0);
	return (code);
}
