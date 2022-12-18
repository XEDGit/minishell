/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sku.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/18 10:56:36 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <time.h>

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
	home = env_get(env, "HOME", 1);
	prompt = env_get(env, "SKU1", 1);
	if (!cwd || !home || !prompt)
	{
		free(prompt);
		free(cwd);
		free(home);
		return (true);
	}
	home_ptr = sk_strnstr(cwd, home, sk_strlen(cwd));
	if (home_ptr)
	{
		*cwd = '~';
		home_ptr += sk_strlen(home);
		len = sk_strlen(home_ptr) + 1;
		sk_strlcpy(cwd + 1, home_ptr, len);
		cwd[len + 1] = 0;
	}
	if (start)
	{
		sk_dprintf(2, "\033[33m~%ds\033[0m\n", (int)difftime(end, start));
		rl_on_new_line();
	}
	*path = sk_strdup(TITLE_COL);
	if (!*path || \
	sk_strjoin(path, prompt, true) || \
	sk_strjoin(path, " ", false) || \
	sk_strjoin(path, cwd, true) || \
	(g_exit_code && sk_strjoin(path, TITLE_RED, false)) || \
	sk_strjoin(path, TITLE_ARR, false))
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

int	parse_skurc(t_env *env, t_env *aliases)
{
	char	*path, *buff_ptr;
	char	buff[1001];
	int		read_ret, err = 0;

	path = env_get(env, "HOME", 1);
	if (sk_strjoin(&path, "/.skurc", false))
		return (1);
	if (!access(path, F_OK) && !access(path, R_OK))
	{
		int fd = open(path, O_RDONLY);
		free(path);
		if (fd == -1)
			return (1);
		read_ret = 1;
		while (read_ret > 0)
		{
			read_ret = read(fd, &buff, 1000);
			if (read_ret > 0)
				buff[read_ret] = 0;
			else
				continue;
			buff_ptr = &buff[0];
			while ((path = sk_strchr(buff_ptr, '\n')))
			{
				*path = 0;
				lexer(buff_ptr, env, aliases, false);
				buff_ptr = path + sizeof(char);
			}
			if (buff_ptr != &buff[read_ret])
				lexer(buff_ptr, env, aliases,false);
		}
		if (read_ret == -1)
			err = error_int("Error reading ~/.skurc", "init", -1, 1);
		close(fd);
	}
	else
		free(path);
	return (err);
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
	completions_generator(env);
	rl_attempted_completion_function = completion;
	if (parse_skurc(env, aliases))
		error_int("Failed to parse ~/.skurc", "init", -1, 0);
	if (argc > 1)
		parse_argv(argv, env, aliases);
	while (1)
	{
		build_title(&title, env, start);
		buffer = readline(title);
		match_completion(0, -1);
		free(title);
		time(&start);
		if (!buffer)
			break ;
		if (*buffer)
			code = lexer(buffer, env, aliases, true);
		free(buffer);
		buffer = 0;
		if (code == 2)
			break ;
	}
	env_free(env);
	env_free(aliases);
	if (code != 2)
		sk_dprintf(2, "exit\n");
	exit(g_exit_code);
}
