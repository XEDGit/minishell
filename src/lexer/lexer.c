/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/31 17:42:49 by lmuzio           ###   ########.fr       */
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
		if (delimiter == 1)
			delimiter = 0;
		c = lexer_multiline_check(input, delimiter);
		if (c == ERROR)
		{
			free(input);
			return (true);
		}
		if (ft_strjoin(buffer, "\n") == ERROR)
			return (error_int("malloc error", 0, -1, ERROR));
		if (ft_strjoin(buffer, input) == ERROR)
			return (error_int("malloc error", 0, -1, ERROR));
	}
	else
		c = delimiter;
	free(input);
	if (c)
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
		ft_dprintf(2, "Error: Parsing failed at char '%c'\n", error);
		g_exit_code = 2;
		return (true);
	}
	return (false);
}

int lexer_semicolon(char *input, t_data *data)
{
	char	**tables;
	int		code;

	if (syntax_check(input, data))
		return (1);
	tables = ft_split(input, "|&");
	if (tables)
		code = parser(tables, data);
	if (code == ERROR || code == 2)
		return (code);
	waitpid(-1, 0, 0);
	return (0);
}


int	lexer(char *input, t_env *env)
{
	char	**semicolon;
	int		count;
	int		code;
	t_data	data;

	data = (t_data){0, 0, 0, 0, 0, env};
	if (multiline_handle(&data, input))
		return (1);
	semicolon = ft_split(data.input, ";");
	count = 0;
	code = 0;
	while (semicolon && semicolon[count] && code == 0)
		code = lexer_semicolon(semicolon[count++], &data);
	free(data.input);
	free2d(semicolon, 0);
	free2dint(data.heredocs, 0);
	return (code);
}
