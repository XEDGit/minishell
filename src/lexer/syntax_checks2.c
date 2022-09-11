/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checks2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 18:33:40 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/11 18:35:22 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

char	*find_next_char(char *start)
{
	start++;
	while (*start && *start == ' ')
		start++;
	return (start);
	
}