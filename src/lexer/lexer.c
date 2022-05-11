/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/08 15:32:59 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 23:08:24 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lexer_multiline_check(char *input, int delimiter)
{
	int	open;

	open = delimiter;
	while (*input && ft_isspace(*input))
		input++;
	if (*input == PIPE || *input == AMP || ampersand_check(input))
		return (ERROR);
	while (*input)
	{
		if (!open && *input == SINGLE_QUOTE)
			open = SINGLE_QUOTE;
		else if (!open && *input == DOUBLE_QUOTE)
			open = DOUBLE_QUOTE;
		else if (open == SINGLE_QUOTE && *input == SINGLE_QUOTE)
			open = 0;
		else if (open == DOUBLE_QUOTE && *input == DOUBLE_QUOTE)
			open = 0;
		else if (!open && (*input == PIPE || *input == AMP))
			if (pipe_check(input))
				return (pipe_check(input));
		input++;
	}
	if (open)
		return (open);
	return (TRUE);
}

int	repeat_readline(char **buffer, char delimiter)
{
	char	*input;
	int		c;

	input = readline(">");
	if (!input)
		return (ERROR);
	if (*input)
	{
		if (delimiter == 1)
			delimiter = 0;
		c = lexer_multiline_check(input, delimiter);
		if (c == ERROR || heredoc_check(input, 0, 0))
		{
			free(input);
			return (1);
		}
		*buffer = ft_strjoin(*buffer, input);
	}
	else
		c = delimiter;
	if (c)
		c = repeat_readline(buffer, c);
	free(input);
	return (c);
}

char	**heredoc_repeat(char *input, int *fds)
{
	char	*buffer;
	int		c;

	fds = malloc(sizeof(int) * 2);
	if (pipe(fds) == ERROR)
		exit(errno);
	while (*input && ft_isspace(*input))
		input++;
	if (!*input)
		return (ERROR);
	c = 0;
	while (input[c] && !ft_isspace(input[c]))
		c++;
	while (FALSE)
	{
		buffer = readline("here >");
		if (!ft_strncmp(buffer, input, c))
			break ;
		else
			write(fds[1], buffer, ft_strlen(buffer));
	}
	close(fds[1]);
	return (0);
}

int	lexer(char *input)
{
	char	**tables;
	t_data	data;
	int		count;

	count = lexer_multiline_check(input, 0);
	if (count == ERROR)
		return (1);
	if (heredoc_check(input, &data) == ERROR)
		return (1);
	data.input = ft_strdup(input);
	if (count)
		count = repeat_readline(&data.input, count);
	if (count)
	{
		if (data.heredoc_c)
			free2d(data.heredocs, 0);
		free(data.input);
		return (count);
	}
	add_history(data.input);
	tables = ft_split(data.input, "|&");
	parser(tables);
	free(data.input);
	free2d(tables, 0);
	return (0);
}
