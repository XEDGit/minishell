/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:44:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 21:17:51 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
	char	*command;
	char	**args;
	int		redirs[3];
}	t_data;

void	set_cmd0(t_data *cmds)
{
	cmds[0].command = "/bin/ls";
	cmds[0].args = malloc(sizeof(char *) * 3);
	cmds[0].args[0] = strdup("/usr/bin/ls");
	cmds[0].args[1] = strdup("-a");
	cmds[0].args[2] = 0;
	cmds[0].redirs[0] = 0;
	cmds[0].redirs[1] = fd[1];
	cmds[0].redirs[2] = 2;
}

void	set_cmd1(t_data *cmds)
{
	cmds[1].command = "/usr/bin/grep";
	cmds[1].args = malloc(sizeof(char *) * (child_num + 1));
	cmds[1].args[0] = strdup("/usr/bin/grep");
	cmds[1].args[1] = strdup("p");
	cmds[1].args[2] = 0;
	cmds[1].redirs[0] = fd[0];
	cmds[1].redirs[1] = 1;
	cmds[1].redirs[2] = 2;
}

void	set_redirects(t_data *cmds, int i)
{
	dup2(cmds[i].redirs[0], 0);
	dup2(cmds[i].redirs[1], 1);
	dup2(cmds[i].redirs[2], 2);
}

int	main(int argc, char **argv, char **envp)
{
	const int	child_num = 2;
	int			fd[2];
	pid_t		child;
	int			i;
	t_data		*cmds;

	if (pipe(fd) == -1)
		exit(1);
	cmds = malloc(sizeof(t_data) * child_num);
	i = 0;
	while (i < child_num)
	{
		child = fork();
		if (!child)
		{
			set_redirects(cmds, i);
			if (execve(cmds[i].command, cmds[i].args, envp))
				exit(1);
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}
