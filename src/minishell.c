/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:20:31 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 01:15:52 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	g_exit_code;

int	semicolon_handle(char *buffer, char **envp, char **envl)
{
	char	**semi_colons_split;
	int		counter;
	int		code;
	t_data	data;

	semi_colons_split = ft_split(buffer, ";");
	if (!semi_colons_split)
		return (ERROR);
	counter = 0;
	while (semi_colons_split[counter])
	{
		data = (t_data){0, 0, 0, 0, 0, envp, envl};
		code = lexer(semi_colons_split[counter], &data);
		if (code == 1)
			ft_printf("Error\n");
		if (code == ERROR || code == 2)
			break ;
		counter++;
	}
	free2d(semi_colons_split, 0);
	return (code);
}

char	**parse_envp(char *envp[])
{
	char	**new;
	int		i;
	int		len;

	i = 0;
	while (envp && envp[i])
		i++;
	new = malloc(sizeof(char **) * (i + 1));
	if (!new)
		return (error_msg("Error: enviromental variable allocation\n"));
	i = 0;
	while (envp && envp[i])
	{
		len = ft_strlen(envp[i]) + 1;
		new[i] = malloc(len);
		if (!new[i])
		{
			free2d(new, i - 1);
			return (error_msg("Error: enviromental variable allocation\n"));
		}
		ft_strlcpy(new[i], envp[i], len);
		i++;
	}
	new[i] = 0;
	return (new);
}

void	error_handle(char **buffer, int code)
{
	// if (code == ERROR)
		// ft_dprintf(2, "Shell error: malloc() failed\n");
	free(*buffer);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		code;
	char	**new_envp;
	char	**envl;

	signals_handler_setup(0);
	rl_outstream = stderr;
	(void)argv;
	(void)argc;
	new_envp = parse_envp(envp);
	envl = parse_envp(0);
	while (1)
	{
		buffer = readline(TITLE);
		if (!buffer)
			break ;
		code = semicolon_handle(buffer, new_envp, envl);
		error_handle(&buffer, code);
		if (code == 2)
			break ;
	}
	free2d(envl, 0);
	free2d(new_envp, 0);
	if (code != 2)
		ft_dprintf(2, "exit\n");
	exit(g_exit_code);
}
