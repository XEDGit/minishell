/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:13:31 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 16:13:32 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	*out_redirect(char **table, t_file *file)
{
	(*table)++;
	if (**table == RIGHT_REDIRECT)
	{
		(*table)++;
		file->flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
		file->flags = O_WRONLY | O_CREAT | O_TRUNC;
	file->name = get_filename(table);
	if (file->name)
		return ((void *) 1);
	return (error_msg("Rx redirect failed", -1));
}
