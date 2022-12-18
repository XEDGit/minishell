/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:53 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 15:59:54 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

//	Correct order:
//	- tilde expansion
//	- variable expansion
//	- * pattern
// wildcard TODO
int	expander(char **tables, t_data *data)
{
	if (!sk_tilde_expand(tables, data->env) || \
		!vars_expansion(tables, data))
		return (false);
	return (true);
}
