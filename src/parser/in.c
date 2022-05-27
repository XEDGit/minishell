#include <parser.h>

static int	left_rdrt(char *file, t_cmd *cmd)
{
	if (cmd->redirects[0] != STDIN_FILENO)
	{
		if (close(cmd->redirects[0]) == ERROR)
			return (error_int("Close error", 0));
	}
	cmd->redirects[0] = open(file, O_RDONLY);
	free(file);
	if (cmd->redirects[0] == ERROR)
		return (error_int("Open error", 0)); // handle precise error
	return (1);
}

static int	here_doc(t_cmd *cmd, int **docs)
{
	static int	count = 0;

	if (cmd->redirects[0] != STDIN_FILENO)
	{
		if (close(cmd->redirects[0]) == ERROR)
			return (error_int("Close error", 0));
	}
	if (!docs[count])
		count = 0;
	cmd->redirects[0] = docs[count++][0];
	return (1);
}

// check errors (<<< <> <<>)
void	*in_redirect(char **table, t_cmd *cmd, int **docs)
{
	char	*file;

	(*table)++;
	if (**table == LEFT_REDIRECT)
	{
		(*table)++;
		if (!here_doc(cmd, docs))
			return (error_msg("Heredoc failed"));
	}
	else
	{
		file = get_filename(table);
		if (!file)
			return (error_msg("File name failed")); // error
		if (!left_rdrt(file, cmd))
			return (error_msg("Left redirect failed")); // left redirect error
	}
	return ((void *) 1);
}
