/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:44 by nmolinel          #+#    #+#             */
/*   Updated: 2022/12/18 10:45:51 by lmuzio           ###   ########.fr       */
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
	if (*str == '(')
	{
		while (*str++ != ')')
			len++;
		return (len + 1);
	}
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
		{
			if (input[1] == '(')
				input += sk_strclen(input, sk_strchr(input, ')'));
			count++;
		}
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

char	*subshell_expansion(char *input, t_data *data)
{
	input = sk_strdup(input);
	*sk_strchr(input, ')') = 0;
	int fds[2];
	if (pipe(&fds[0]))
	{
		free(input);
		return ((char *)(long)error_int("error opening pipe", "subsh expansion", 1, 0));
	}
	sk_subshell(input, data->env, data->aliases, true, fds[1]);
	free(input);
	char buffer[1001] = {0}, *output = malloc(1);
	int len;
	if (!output)
		return ((char *)(long)error_int("malloc fail", "subsh expansion", 1, 0));
	output[0] = 0;
	while ((len = read(fds[0], &buffer, 1000)) > 0)
	{
		buffer[len] = 0;
		if (sk_strjoin(&output, buffer, false))
			return ((char *)(long)error_int("malloc in strjoin fail", "subsh expansion", 1, 0));
		if (len < 1000)
		{
			if (output[sk_strlen(output) - 1] == '\n')
				output[sk_strlen(output) - 1] = 0;
			break ;
		}
	}
	if (len == -1)
		return ((char *)(long)error_int("malloc in strjoin fail", "subsh expansion", 1, 0));
	if (close(fds[0]))
		return ((char *)(long)error_int("closing pipe read end", "subsh expansion", 1, 0));
	return (output);
}

int	set_vars(char **vars, char *input, t_data *data)
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
			else if (*input == '(')
			{
				vars[i] = subshell_expansion(input + 1, data);
				input += sk_strclen(input, sk_strchr(input, ')'));
			}
			else if (!*input || is_del(*input))
				vars[i] = sk_strdup("$");
			else if (*input >= '0' && *input <= '9')
				vars[i] = sk_strdup("");
			else
				vars[i] = get_var(input, data->env);
			if (!vars[i++])
				return (free_2d_ret(vars, i - 1, 0));
		}
		input++;
	}
	vars[i] = 0;
	return (true);
}
