/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:18:27 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/31 16:18:49 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int	check_double_commands(char *str, int c, int diff)
{
	if (c == 0 && diff == -1)
		return (false);
	c = c + diff;
	while (ft_isspace(str[c]))
		c += diff;
	if (str[c] && c >= 0 && str[c] != '|' && str[c] != '&')
	{
		if (diff == -1)
			diff = 40;
		else
			diff = str[c];
		ft_dprintf(2, "Error parsing symbol '%c'\n", diff);
		return (true);
	}
	return (false);
}
