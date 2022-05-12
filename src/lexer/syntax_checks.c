/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/08 15:32:59 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 23:08:01 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ampersand_check(char *input)
{
	while (*input)
	{
		if (*input == AMP)
		{
			input++;
			if (*input != AMP)
				return (ERROR);
			else
				input++;
		}
		if (*input)
			input++;
	}
	return (TRUE);
}

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

int	heredoc_check(char *input, t_data *data)
{
	int	c;

	c = 0;
	if (data)
	{
		data->heredoc_c = heredoc_check(input, 0);
		data->heredocs = malloc((data->heredoc_c + 1) * sizeof(int *));
		if (!data->heredocs)
			exit(errno);
		data->heredocs[data->heredoc_c] = 0;
	}
	while (*input)
	{
		if (*input == '<')
		{
			input++;
			if (*input++ == '<')
			{
				if (data && heredoc_repeat(input, &data->heredocs[c]) == ERROR)
					return (ERROR);
				c++;
			}
		}
		if (*input)
			input++;
	}
	return (c);
}
