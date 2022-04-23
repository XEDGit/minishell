/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multifork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 05:23:21 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/23 08:04:53 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*itoa(int n)
{
	char	*res;
	int		i;
	int		temp;

	i = 1;
	temp = n;
	while (temp != 0)
	{
		temp = temp / 10;
		i++;
	}
	res = malloc(i);
	if (!res)
		exit(1);
	res[i - 1] = 0;
	while (i >= 0)
	{
		res[--i] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}

void	a(void)
{
	printf("func1\n");
}

void	b(void)
{
	printf("func2\n");
}

int	main(void)
{
	const int	max_childs = 6;
	int			i;
	pid_t		*children;
	int			status;
	void		(*f[2])(void);

	f[0] = &a;
	f[1] = &b;
	children = malloc(sizeof(pid_t) * max_childs);
	i = 0;
	printf("Parent: %s\n\n", itoa(getpid()));
	//create multiple children from a parent without forking any child process	:	Use this when forking a child for every pipe
	while (i < max_childs)
	{
		children[i] = fork();
		if (!children[i])
		{
			f[i % 2]();
			exit(0);
		}
		i++;
	}
	//end
	free(children);
	exit(0);
}
