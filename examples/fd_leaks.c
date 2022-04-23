/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/29 00:00:00 by Martin Uedi       #+#    #+#             */
/*   Updated: 2022/04/23 06:20:47 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	filename[100];
	FILE	*fp;
	size_t	i;

	i = 0;
	while (i++ < 1500)
	{
		sprintf(filename, "/tmp/%010ld.txt", i);
		fp = fopen(filename, "w");
		if (fp == NULL)
		{
			printf("i = %6ld: failed!\n", i);
			remove(filename);
			exit(1);
		}
		if (remove(filename) == 1)
		{
			perror("Failed to remove file");
			exit(2);
		}
		if (i % 100 == 0)
			printf("i = %6ld: ok.\n", i);
	}
	exit(0);
}
