/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:32:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/16 20:23:09 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	double_char_check(char *input, char ch)
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

int	heredoc_init(char *input, t_data *data)
{
	data->heredoc_c = heredoc_check(input, 0);
	data->heredocs = malloc((data->heredoc_c + 1) * sizeof(int *));
	if (!data->heredocs)
	{
		printf("Error: failed to allocate heredoc pipe\n");
		return (ERROR);
	}
	data->heredocs[data->heredoc_c] = 0;
	return (false);
}

int	heredoc_check(char *input, t_data *data)
{
	int	c;
	int	code;

	c = 0;
	if (data && heredoc_init(input, data) == ERROR)
		return (ERROR);
	while (*input)
	{
		input += skip_quotes(input);
		if (*input++ == '<')
		{
			if (*input++ == '<')
			{
				if (data)
				{
					data->heredocs[c] = malloc(sizeof(int) * 2);
					code = heredoc_repeat(input, data->heredocs[c]);
					if (code == ERROR)
						return (ERROR);
				}
				c++;
			}
		}
	}
	return (c);
}
