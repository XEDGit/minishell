#include <parser.h>

// char	*expand_var(char *key, char **envp)
// {
// 	size_t	n;

// 	while (*envp)
// 	{
// 		n = ft_strchr(*envp, '=') - (*envp);
// 		if (!ft_strncmp(key, *envp, n++))
// 			return (*envp + n);
// 		envp++;
// 	}
// 	return (0);
// }

// [*,*,0]
// dsa$ca $PWD

/*
*	expand $VAR only if not inside ''
*	expand * combinations
*	<TODO cat >dsa$PWD|cat<TODO
*/
int	count_vars(char *input)
{
	int	count;
	int	open;

	count = 0;
	while (*input)
	{
		open = is_open(*input);
			// (!open && *input == '*')
		if ((*input == '$' && open != SINGLE_QUOTE))
			count++;
		input++;
	}
	return (count);
}

int	set_vars(char **vars, char *input)
{
	t_var	var;
	int		open;
	int		i;

	i = 0;
	while (*input)
	{
		open = is_open(*input);
			// (!open && *input == '*')
		if (*input == '$' && open != SINGLE_QUOTE)// check delimiter and null
		{
			get_var_name(&var, ++input);
			// printf("VARNAME: %s$\n", var.p);
			vars[i] = getenv(var.p);
			// printf("EXPANDE: %s$\n", vars[i]);
			// printf("VARLENG: %d\n", var.length);
			var.p[var.length] = var.c;
			i++;
		}
		input++;
	}
	vars[i] = 0;
	return (1);
}

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

char	*expand_vars(char **vars, char *input)
{
	char	*out;
	int		open;
	int		i;
	int		index;

	out = malloc((sizeof(char) * (get_out_size(vars, input) + 1)));
	if (!out)
		return (false);
	i = 0;
	index = 0;
	while (*input)
	{
		open = is_open(*input);
		if (*input == '$' && open != SINGLE_QUOTE)
		{
			input++;
			strcpy(out + i, vars[index]);
			i += ft_strlen(vars[index++]);
			input += var_name_length(input);
			continue ;
		}
		out[i++] = *input++;
	}
	out[i] = 0;
	return (out);
}

int	var_expand(char **tables, t_env *env)
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
		if (!set_vars(vars, *tables))
		{
			free(vars);
			return (0);
		}
		new_table = expand_vars(vars, *tables);
		free(vars);
		if (!new_table)
			return (error_int("Expander allocation failed", 0, 1, 0));
		free(*tables);
		*tables = new_table;
	}
	return (1);
}

char	*clean_quotes(char *table)
{
	int	i;
	int	open;

	i = 0;
	while (*table)
	{
		open = is_open(*table);
		if ((!open && (*table == '\'' || *table == '\"')) || \
		(open && *table == open))
			*table = ' ';
		table++;
	}
	
	return table;
}

//	Correct order:
//	- tilde expansion
//	- variable expansion
//	- * pattern
//	- unquoted ' " removed
int	expander(char **tables, t_env *env)
{
	int	i;

	i = 0;
	while (tables[i])
	{
		if (!ft_tilde_expand(&tables[i], env) || !var_expand(&tables[i], env))
			return (false);
		// wildcard TODO
		clean_quotes(tables[i]);
		i++;
	}
	return (true);
}
