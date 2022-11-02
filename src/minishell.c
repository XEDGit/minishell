/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:20:31 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 17:33:11 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <sys/types.h>
#include <sys/wait.h>

int	g_exit_code;

int	semicolon_handle(char *buffer, t_env *env)
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
		data = (t_data){0, 0, 0, 0, 0, env};
		code = lexer(semi_colons_split[counter], &data);
		if (code == 1)
			error_int("Error parsing syntax", 0, 2, 0);
		if (code == ERROR || code == 2)
			break ;
		counter++;
		waitpid(-1, 0, 0);
	}
	free2d(semi_colons_split, 0);
	return (code);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		code;
	t_env	*env;

	signals_handler_setup(0);
	rl_outstream = stderr;
	(void)argv;
	(void)argc;
	env = env_setup(envp);
	if (!env)
		return (44);
	while (1)
	{
		buffer = readline(TITLE);
		if (!buffer)
			break ;
		code = semicolon_handle(buffer, env);
		free(buffer);
		if (code == 2)
			break ;
	}
	env_free(env);
	if (code != 2)
		ft_dprintf(2, "exit\n");
	exit(g_exit_code);
}
