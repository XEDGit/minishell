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
		if (ft_strjoin(buffer, input) == ERROR)
			return (error_int("malloc error", 0, -1, ERROR));
	}
	else
		c = delimiter;
	if (!input || syntax_check(input, data))
		return (error_int("syntax error", 0, 2, ERROR));
	if (c)
		c = repeat_readline(buffer, c, data);
	free(input);
	return (c);
}

int	syntax_check(char *input, t_data *data)
{
	int	error;

	if (!check_standalone_redirects(input))
		return (error_int("syntax error", 0, 2, 1));
	error = io_check(input);
	if (error)
	{
		ft_dprintf(2, "Error: Parsing failed at char '%c'\n", error);
		g_exit_code = 2;
		return (true);
	}
	error = heredoc_check(input, data);
	if (error < 0)
	{
		if (error == ERROR)
			ft_dprintf(2, "Error: An error in heredoc functioning happened\n");
		return (true);
	}
	return (false);
}

int	lexer(char *input, t_data *data)
{
	char	**tables;
	int		count;

	count = lexer_multiline_check(input, 0);
	if (count == ERROR || syntax_check(input, data))
		return (1);
	data->input = ft_strdup(input);
	if (!data->input)
		return (free2dint(data->heredocs, 0));
	if (count)
		count = repeat_readline(&data->input, count, data);
	add_history(data->input);
	if (count || parenthesis_check(data->input))
	{
		free2dint(data->heredocs, 0);
		free(data->input);
		return (count);
	}
	tables = ft_split(data->input, "|&");
	if (tables)
		count = parser(tables, data);
	free(data->input);
	free2dint(data->heredocs, 0);
	return (count);
}
