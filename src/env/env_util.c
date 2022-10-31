/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:45:44 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/10/31 15:50:24 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <ft_libc.h>

char	*copy_var(char *p, int i)
{
	char	*out;

	out = malloc(sizeof(char) * ft_strlen(p) + 1);
	if (out)
		ft_strlcpy(out, p, ft_strlen(p) + 1);
	return (out);
}

t_buffvar	*add_var(t_buffvar *buff, char *var, int index)
{
	if (index >= 0)
	{
		free(buff->mem[index]);
		buff->mem[index] = var;
	}
	else
	{
		if (!buff_checker(buff))
		{
			free(var);
			return (0);
		}
		buff->mem[buff->index++] = var;
		buff->mem[buff->index] = 0;
	}
	return (buff);
}

bool	valid_varname(char *name)
{
	if (ft_isdigit(*name) || *name == '=' || \
	(*name == '$' && !*(name + 1)) || *name == ' ')
		return (false);
	while (*name && *name != '=')
	{
		if (*name == ' ' || *name == '+')
			return (false);
		name++;
	}
	return (true);
}
