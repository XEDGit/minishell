/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/25 21:48:05 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <time.h>
// #include <sys/types.h>
// #include <sys/wait.h>

int	g_exit_code;

int build_title(char **path, t_env *env, time_t start)
{
	char	*cwd;
	char	*prompt;
	char	*home;
	char	*home_ptr;
	int		len;
	time_t	end;

	time(&end);
	cwd = getcwd(0, 0);
	home = env_get(env, "HOME", 0);
	prompt = env_get(env, "SKU1", 0);
	if (!cwd || !home || !prompt)
	{
		free(prompt);
		free(cwd);
		free(home);
		return (true);
	}
	home_ptr = ft_strnstr(cwd, home, ft_strlen(cwd));
	if (home_ptr)
	{
		*cwd = '~';
		home_ptr += ft_strlen(home);
		len = ft_strlen(home_ptr) + 1;
		ft_strlcpy(cwd + 1, home_ptr, len);
		cwd[len + 1] = 0;
	}
	if (start)
		ft_dprintf(2, "\033[33m~%ds\033[0m\n", (int)difftime(end, start));
	*path = ft_strdup(TITLE_COL);
	if (!*path || \
	ft_strjoin(path, prompt, true) || \
	ft_strjoin(path, " ", false) || \
	ft_strjoin(path, cwd, true) || \
	(g_exit_code && ft_strjoin(path, TITLE_RED, false)) || \
	ft_strjoin(path, TITLE_ARR, false))
	{
		free(cwd);
		free(home);
		free(prompt);
		return (true);
	}
	free(cwd);
	free(home);
	free(prompt);
	return (false);
}

int	main(int argc, char **argv, char *envp[])
{
	char	*buffer;
	char	*title;
	int		code;
	t_env	*env;
	t_env	*aliases;
	time_t	start;

	start = 0;
	signals_handler_setup(0);
	rl_outstream = stderr;
	g_exit_code = 0;
	aliases = env_create((char **){0});
	env = env_setup(envp);
	if (!env)
		return (44);
	if (argc > 1)
		parse_argv(argv, env, aliases);
	while (1)
	{
		build_title(&title, env, start);
		buffer = readline(title);
		free(title);
		time(&start);
		if (!buffer)
			break ;
		if (*buffer)
			code = lexer(buffer, env, aliases);
		else
			g_exit_code = 0;
		free(buffer);
		buffer = 0;
		if (code == 2)
			break ;
	}
	env_free(env);
	env_free(aliases);
	if (code != 2)
		ft_dprintf(2, "exit\n");
	exit(g_exit_code);
}
