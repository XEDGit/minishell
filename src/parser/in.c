#include <parser.h>

static int	here_doc(t_cmd *cmd, int **docs)
{
	static int	count;

	if (cmd->redirects[0] != STDIN_FILENO)
	{
		if (close(cmd->redirects[0]) == ERROR)
			return (error_int("Close error", cmd->cmd, 1, 0));
	}
	if (!docs[count])
		count = 0;
	cmd->redirects[0] = docs[count++][0];
	return (1);
}

// meta-> '>' '<' '&' '|' '(' ')' '$'
char	*skip_word(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
	while (**input && !ft_isspace(**input))
	{
		if (!is_open(**input) && (**input == '<' || **input == '>'))
			break ;
		(*input)++;
	}
	return (*input);
}

void	*in_redirect(char **table, t_file *file)
{
	file->name = 0;
	file->flags = O_RDONLY;
	(*table)++;
	if (**table == LEFT_REDIRECT)
	{
		(*table)++;
		skip_word(table);
		file->here = true;
	}
	else
	{
		file->name = get_filename(table);
		if (!file->name)
			return (error_msg("File name failed", 2)); // error
	}
	return ((void *) 1);
}
