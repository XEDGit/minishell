/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 06:20:59 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/23 06:24:14 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t	child;

	printf("Parent: %d\n", getpid());
	child = fork();
	if (!child)
		printf("Hi, I'm the child: %d\n", getpid());
	else
		printf("Hi, I'm the parent: %d\n", getpid());
	exit(0);
}
