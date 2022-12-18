/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:46:54 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/18 10:46:56 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int sk_subshell(char *input, t_env *env, t_env *aliases, int tofork, int outfd)
{
	pid_t	child;

	child = 0;
	if (tofork)
	{
		child = fork();
		if (child == -1)
			return (error_int("Error forking process", "subshell", -1, true));
	}
	if (!child)
	{
		if (tofork && outfd)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		lexer(input, env, aliases, false);
		env_free(env);
		env_free(aliases);
		exit(g_exit_code);
	}
	if (outfd)
		close(outfd);
	if (tofork)
		watch_child(child);
	return (false);
}
