/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:18:27 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/15 13:22:22 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	multiline_handle(t_data *data, char *input, int c, bool save_history)
{
	data->input = sk_strdup(input);
	if (!data->input)
		return (error_int("error allocating user input", "malloc", -1, 1));
	if (c)
		c = repeat_readline(&data->input, c, data);
	if (save_history)
		add_history(data->input);
	if (c || syntax_check(data->input, data))
	{
		free(data->input);
		return (1);
	}
	c = heredoc_check(data->input, data);
	if (c < 0)
	{
		free(data->input);
		if (c == ERROR)
			error_int("an error during functioning happened\n", "heredoc", 1, 0);
		return (true);
	}
	return (0);
}

int	check_double_commands(char *str, int c, int diff)
{
	static bool	skip_one = false;

	if (skip_one)
	{
		skip_one = false;
		return (false);
	}
	if (c == 0 && diff == -1)
		return (false);
	if (str[c - 1] == '$')
	{
		skip_one = true;
		return (false);
	}
	c = c + diff;
	while (sk_isspace(str[c]))
		c += diff;
	if (str[c] && c >= 0 && str[c] != '|' && str[c] != '&')
		return (true);
	return (false);
}

int	truncate_delimiter(char *del)
{
	if (*del == '<' || *del == '>' || *del == '|' \
	|| *del == '&' || *del == '\n' || *del == ';' \
	|| sk_isspace(*del))
	{
		*del = 0;
		return (true);
	}
	return (false);
}
