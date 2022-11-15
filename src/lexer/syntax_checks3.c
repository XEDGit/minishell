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

int	multiline_handle(t_data *data, char *input, int c)
{
	data->input = ft_strdup(input);
	if (!data->input)
		return (error_int("Error allocating user input", "malloc", -1, 1));
	if (c)
		c = repeat_readline(&data->input, c, data);
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
			ft_dprintf(2, "Error: An error in heredoc functioning happened\n");
		return (true);
	}
	return (0);
}

int	check_double_commands(char *str, int c, int diff)
{
	if (c == 0 && diff == -1)
		return (false);
	c = c + diff;
	while (ft_isspace(str[c]))
		c += diff;
	if (str[c] && c >= 0 && str[c] != '|' && str[c] != '&')
	{
		if (diff == -1)
			diff = 40;
		else
			diff = str[c];
		ft_dprintf(2, "Error parsing symbol '%c'\n", diff);
		return (true);
	}
	return (false);
}

int	truncate_delimiter(char *del)
{
	if (*del == '<' || *del == '>' || *del == '|' \
	|| *del == '&' || *del == '\n' || *del == ';' \
	|| ft_isspace(*del))
	{
		*del = 0;
		return (true);
	}
	return (false);
}
