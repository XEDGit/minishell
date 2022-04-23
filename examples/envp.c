/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 03:16:45 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/23 08:06:51 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//We can write on enviromental variables, here the first letter is set to 'z'
int	main(int argc, char **argv, char **envp)
{
	**envp = 'z';
	while (*envp)
		printf("%s\n", *envp++);
	exit(0);
}
