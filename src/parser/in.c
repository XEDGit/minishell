/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:12:33 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 16:41:41 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

char	*skip_word(char **input)
{
	while (sk_isspace(**input))
		(*input)++;
	while (**input)
	{
		if (!is_open(**input) && \
		((**input == '<' || **input == '>') || sk_isspace(**input)))
			break ;
		(*input)++;
	}
	while (sk_isspace(**input))
		(*input)++;
	return (*input);
}

void	*in_redirect(char **table, t_file *file)
{
	file->name = 0;
	file->flags = O_RDONLY;
	(*table)++;
	if (**table == LEsk_REDIRECT)
	{
		(*table)++;
		skip_word(table);
		file->here = true;
	}
	else
	{
		file->name = get_filename(table);
		if (!file->name)
			return (error_msg("File name failed", 2));
	}
	return ((void *) 1);
}
