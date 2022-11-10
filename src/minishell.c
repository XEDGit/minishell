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
		code = lexer(buffer, env);
		free(buffer);
		if (code == 2)
			break ;
	}
	env_free(env);
	if (code != 2)
		ft_dprintf(2, "exit\n");
	exit(g_exit_code);
}
