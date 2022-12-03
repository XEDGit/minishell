/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 16:04:44 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/02 15:44:08 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	is_del(char c)
{
	if (c == ' ' || c == '$' || c == '<' || c == '>' || c == '/' \
		|| c == '&' || c == '|' || c == '\'' || c == '\"' || c == '=')
		return (1);
	return (0);
}

int	var_name_length(char *str)
{
	int	len;

	len = 0;
	if (*str == '?' || (*str >= '0' && *str <= '9'))
		return (1);
	while (*str && !is_del(*str++))
		len++;
	return (len);
}

int	count_vars(char *input)
{
	int	count;
	int	open;

	count = 0;
	while (*input)
	{
		open = is_open(*input);
		if ((*input == '$' && open != SINGLE_QUOTE))
			count++;
		input++;
	}
	return (count);
}

char	*get_var(char *str, t_env *env)
{
	int		i;
	char	*name;
	char	*var;

	i = 0;
	name = malloc(sizeof(char) * (sk_strclen(str, " ") + 1));
	if (!name)
		return (0);
	while (*str && !is_del(*str))
		name[i++] = *str++;
	name[i] = 0;
	var = env_get(env, name, 0);
	free(name);
	if (!var)
		return (0);
	return (var);
}

int	set_vars(char **vars, char *input, t_env *env)
{
	int		i;
	int		open;

	i = 0;
	while (*input)
	{
		open = is_open(*input);
		if (*input == '$' && open != SINGLE_QUOTE)
		{
			if (*(++input) == '?')
				vars[i] = sk_itoa(g_exit_code);
			else if (!*input || is_del(*input))
			{
				vars[i++] = sk_strdup("$");
				continue ;
			}
			else if (*input >= '0' && *input <= '9')
			{
				vars[i++] = sk_strdup("");
				continue ;
			}
			else
				vars[i] = get_var(input, env);
			if (!vars[i++])
				return (free_2d_ret(vars, i - 1, 0));
		}
		input++;
	}
	vars[i] = 0;
	return (true);
}
