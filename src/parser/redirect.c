#include <parser.h>

// Retrive and expand the redirect word(filename)
char    *get_filename(char **input)
{
    char    *tmp;
    char    *name;
	int		len;

	len = 0;
    while (ft_isspace(**input))
        (*input)++;
	tmp = *input;
	while (*tmp && !ft_isspace(*tmp++))// check other metachars
		len++;
	tmp = malloc(sizeof(char) * (++len));
	if (!tmp)
		return ((char *) error_msg("Malloc failed"));
	ft_strlcpy(tmp, *input, len);
	*input += len - 1;
	name = remove_quotes(tmp);
	free(tmp);
	if (!name)
		return ((char *) error_msg("Remove quotes failed"));
	printf("Filename: %s\n", name);
    return (name);
}

char	*set_redirects(char *table, t_cmd *cmd, int **docs)
{
	int		open;
	char	*file;

	open = 0;
	char	*rest = malloc(sizeof(char) * 50);
	int	counter = 0;
	while (*table)
	{
		if (!open && *table == SINGLE_QUOTE)
			open = SINGLE_QUOTE;
		else if (!open && *table == DOUBLE_QUOTE)
			open = DOUBLE_QUOTE;
		else if (open == SINGLE_QUOTE && *table == SINGLE_QUOTE)
			open = 0;
		else if (open == DOUBLE_QUOTE && *table == DOUBLE_QUOTE)
			open = 0;
		else if (!open && *table == '>')
		{
			if (*(++table) == '>')
			{
				table++;
				file = get_filename(&table);
				if (!file)
					return (error_msg("File name failed")); // error
				if (!append(file, cmd))
					return (error_msg("Append failed")); // append error
			}
			else
			{
				file = get_filename(&table);
				if (!file)
					return (error_msg("File name failed")); // error
				if (!right_rdrt(file, cmd))
					return (error_msg("Right redirect failed")); // right redirect error
			}
			// printf("table restart: %s\n", table);
			continue ;
		}
		else if (!open && *table == '<')
		{
			if (*(++table) == '<')
			{
				table++;
				// heredoc() TODO
			}
			else
			{
				file = get_filename(&table);
				if (!file)
					return (error_msg("File name failed")); // error
				if (!left_rdrt(file, cmd))
					return (error_msg("Left redirect failed")); // left redirect error
			}
			// printf("table restart: %s\n", table);
			continue ;
		}
		// printf("t: %s\n", table);
		rest[counter++] = *table++;
	}
	rest[counter] = 0;
	return (rest);
}
