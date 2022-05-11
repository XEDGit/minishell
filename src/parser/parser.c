/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:22:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/11 05:20:33 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser(char **tables)
{
	int	c;

	c = 0;
	while (*tables)
		printf("split[%d]: %s\n", c++, *tables++);
	return (0);
}
