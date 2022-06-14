/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 19:05:18 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/06/13 18:50:06 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	heredoc_routine(char *input, int c, int *fds)
{
	char		*buffer;
	static int	lines = 0;

	buffer = readline("here >");
	if (!buffer || !ft_strexcmp(buffer, input, c, "<>"))
	{
		lines = 0;
		free(buffer);
		return (ERROR);
	}
	if (lines)
		write(fds[1], "\n", 1);
	write(fds[1], buffer, ft_strlen(buffer));
	free(buffer);
	lines++;
	return (false);
}

int	heredoc_repeat(char *input, int *fds)
{
	int		c;

	if (pipe(fds) == ERROR)
	{
		ft_dprintf(2, "Error opening pipe\n");
		return (ERROR);
	}
	while (*input && ft_isspace(*input))
		input++;
	if (!*input)
		return (ERROR);
	input = remove_quotes(input);
	if (!input)
		return (ERROR);
	c = 0;
	while (input[c] && !ft_isspace(input[c]) && \
	input[c] != PIPE && input[c] != AMP)
		c++;
	while (1)
		if (heredoc_routine(input, c, fds) == ERROR)
			break ;
	free(input);
	close(fds[1]);
	return (0);
}

int	heredoc_init(char *input, t_data *data, int *c)
{
	int	**mall;
	int	rcount;

	if (data->heredocs)
	{
		*c = data->heredoc_c;
		data->heredoc_c += heredoc_check(input, 0);
		mall = malloc((data->heredoc_c + 1) * sizeof(int *));
		if (!mall)
			return (ERROR);
		mall[data->heredoc_c] = 0;
		rcount = -1;
		while (data->heredocs[++rcount])
			mall[rcount] = data->heredocs[rcount];
		free(data->heredocs);
		data->heredocs = mall;
		return (false);
	}
	data->heredoc_c = heredoc_check(input, 0);
	data->heredocs = malloc((data->heredoc_c + 1) * sizeof(int *));
	if (!data->heredocs)
		return (ERROR);
	data->heredocs[data->heredoc_c] = 0;
	return (false);
}

int	free_heredocs(int **tofree, int len)
{
	while (len >= 0)
	{
		if (tofree[len])
			close(tofree[len][1]);
		free(tofree[len]);
		len--;
	}
	free(tofree);
	return (ERROR);
}

int	heredoc_check(char *input, t_data *data)
{
	int	c;
	int	code;

	c = 0;
	if (data && heredoc_init(input, data, &c) == ERROR)
		return (ERROR);
	while (*input)
	{
		input += skip_quotes(input);
		if (*input++ == '<' && *input == '<')
		{
			if (data)
			{
				data->heredocs[c] = malloc(sizeof(int) * 2);
				if (!data->heredocs[c])
					return (free_heredocs(data->heredocs, c - 1));
				code = heredoc_repeat(++input, data->heredocs[c]);
				if (code == ERROR)
					return (free_heredocs(data->heredocs, c));
			}
			c++;
		}
	}
	return (c);
}
