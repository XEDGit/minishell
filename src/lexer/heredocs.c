/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:05:18 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/15 17:29:46 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	heredoc_routine(char *input, int *fds)
{
	char		*buffer;
	static int	lines = 0;

	if (!lines)
		signals_handler_setup(3);
	buffer = readline("here >");
	if (!buffer || !sk_strcmp(buffer, input))
	{
		if (lines && write(fds[1], "\n", 1) == -1)
			{} // Can't act upon write failure
		lines = 0;
		free(buffer);
		return (ERROR);
	}
	if ((lines && write(fds[1], "\n", 1) == -1) || write(fds[1], buffer, sk_strlen(buffer)) == -1)
		return (free(buffer), ERROR);
	free(buffer);
	lines++;
	return (false);
}

int	wait_heredoc(pid_t here_pid)
{
	int	stat;

	if (here_pid == -1)
		return (error_int("error forking process for heredoc", 0, -1, 1));
	signals_handler_setup(1);
	waitpid(here_pid, &stat, 0);
	signals_handler_setup(0);
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
			sk_dprintf(2, "\n");
		return (1);
	}
	return (0);
}

int	heredoc_repeat(char *d, int *fds)
{
	pid_t	here_pid;

	if (pipe(fds) == ERROR)
	{
		sk_dprintf(2, SHELLNAME"error opening pipe for heredoc\n");
		return (ERROR);
	}
	while (sk_isspace(*d))
		d++;
	d = sk_strdup(d);
	erase_chars(d, "\'\"");
	int i = 0;
	while (d[i] && !truncate_delimiter(&d[i]))
		i++;
	here_pid = fork();
	if (!here_pid)
		while (1)
			if (heredoc_routine(d, fds) == ERROR)
				exit(0);
	g_exit_code = wait_heredoc(here_pid);
	free(d);
	close(fds[1]);
	if (g_exit_code)
		return (-2);
	return (0);
}

int	heredoc_init(char *input, t_data *data)
{
	data->heredoc_c = heredoc_check(input, 0);
	data->heredocs = malloc((data->heredoc_c + 1) * sizeof(int *));
	if (!data->heredocs)
		return (ERROR);
	data->heredocs[data->heredoc_c] = 0;
	data->heredoc_c = 0;
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
		if (*input++ == '<' && *input == '<')
		{
			if (data)
			{
				data->heredocs[c] = malloc(sizeof(int) * 2);
				if (!data->heredocs[c])
					return (error_free2dint(data->heredocs, c, ERROR));
				code = heredoc_repeat(++input, data->heredocs[c]);
				if (code)
					return (error_free2dint(data->heredocs, c, code));
			}
			c++;
		}
	}
	return (c);
}
