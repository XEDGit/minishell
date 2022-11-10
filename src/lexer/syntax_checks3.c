/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:18:27 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/31 16:18:49 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	multiline_handle(t_data *data, char *input)
{
	int	count;

	count = lexer_multiline_check(input, 0);
	if (count == ERROR)
		return (error_int("Syntax error", 0, 2, 1));
	data->input = ft_strdup(input);
	if (!data->input)
		return (error_int("Error allocating user input", "malloc", -1, 1));
	if (count)
		count = repeat_readline(&data->input, count, data);
	add_history(data->input);
	if (count || syntax_check(data->input, data))
	{
		free(data->input);
		return (1);
	}
	count = heredoc_check(input, data);
	if (count < 0)
	{
		free(data->input);
		if (count == ERROR)
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

void	truncate_delimiter(char *del)
{
	while (*del)
	{
		if (*del == '<' || *del == '>' || *del == '|' \
		|| *del == '&' || *del == '\n' || *del == ';' \
		|| ft_isspace(*del))
		{
			*del = 0;
			return ;
		}
		del++;
	}
}