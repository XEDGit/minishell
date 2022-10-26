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
	if (*str == '?')
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
	char	c;
	int		i;
	char	*name;
	char	*var;

	i = 0;
	name = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
		if (*input == '$' && open != SINGLE_QUOTE)// check delimiter and null
		{
			if (*(++input) == '?')
				vars[i] = ft_itoa(g_exit_code);
			else if (!*input || *input == '=' || *input == ' ')
			{
				vars[i++] = ft_strdup("$");
				continue ;
			}
			else
				vars[i] = get_var(input, env);
			if (!vars[i])
			{
				free2d(vars, 0);
				return (false);
			}
			i++;
		}
		input++;
	}
	vars[i] = 0;
	return (true);
}
