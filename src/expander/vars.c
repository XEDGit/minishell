/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:03:44 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 16:03:45 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	get_out_size(char **vars, char *input)
{
	int	i;
	int	size;
	int	open;

	i = 0;
	size = 0;
	while (*input)
	{
		open = is_open(*input);
		if (*input == '$' && open != SINGLE_QUOTE)
		{
			size += ft_strlen(vars[i++]);
			input++;
			input += var_name_length(input);
			continue ;
		}
		size++;
		input++;
	}
	return (size);
}

char	*expand_vars_table(char **vars, char *input, int i, int index)
{
	char	*out;
	int		open;
	size_t	len;

	len = get_out_size(vars, input) + 1;
	out = malloc(sizeof(char) * len);
	if (!out)
		return (false);
	while (*input)
	{
		open = is_open(*input);
		if (*input == '$' && open != SINGLE_QUOTE)
		{
			input++;
			ft_strlcpy(out + i, vars[index], len);
			i += ft_strlen(vars[index++]);
			input += var_name_length(input);
			continue ;
		}
		out[i++] = *input++;
	}
	out[i] = 0;
	return (out);
}

int	vars_expansion(char **tables, t_env *env)
{
	char	**vars;
	int		n_vars;
	char	*new_table;

	n_vars = count_vars(*tables);
	if (n_vars)
	{
		vars = malloc(sizeof(char *) * (n_vars + 1));
		if (!vars)
			return (error_int("Expander allocation failed", 0, 1, 0));
		if (!set_vars(vars, *tables, env))
			return (error_int("Expander allocation failed", 0, 1, 0));
		new_table = expand_vars_table(vars, *tables, 0, 0);
		free2d(vars, 0);
		if (!new_table)
			return (error_int("Expander allocation failed", 0, 1, 0));
		free(*tables);
		*tables = new_table;
	}
	return (1);
}
