/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:12:14 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 16:37:55 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	free_files(t_file *lst)
{
	t_file	*i;
	t_file	*t;

	i = lst;
	while (i)
	{
		t = i;
		i = t->next;
		if (t->name)
			free(t->name);
		free(t);
	}
}

t_file	*add_file(t_cmd *cmd)
{
	t_file	*last;
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (0);
	file->dest = 1;
	if (!cmd->files)
	{
		cmd->files = file;
		return (file);
	}
	last = cmd->files;
	while (last)
	{
		if (!last->next)
		{
			last->next = file;
			break ;
		}
		last = last->next;
	}
	return (file);
}

int	get_length(char *input)
{
	int		len;

	len = 0;
	while (input[len] && !ft_isspace(input[len]))
	{
		if (!is_open(input[len]) && (input[len] == '<' || input[len] == '>'))
			break ;
		len++;
	}
	return (len);
}

// Retrive and expand the redirect word(filename)
char	*get_filename(char **input)
{
	char	*tmp;
	char	*name;
	int		len;

	while (ft_isspace(**input))
		(*input)++;
	tmp = *input;
	len = get_length(*input);
	if (!len)
		return (0);
	tmp = malloc(sizeof(char) * (++len));
	if (!tmp)
		return ((char *) error_msg("Malloc failed", -1));
	ft_strlcpy(tmp, *input, len);
	*input += len - 1;
	name = remove_quotes(tmp);
	free(tmp);
	if (!name)
		return ((char *) error_msg("Remove quotes failed", -1));
	return (name);
}
