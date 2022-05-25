#include <parser.h>

int	left_rdrt(char *file, t_cmd *cmd)
{
	if (cmd->redirects[0] != STDIN_FILENO)
		close(cmd->redirects[0]); // handle error
	cmd->redirects[0] = open(file, O_RDONLY);
	free(file);
	if (cmd->redirects[0] == ERROR)
		return (error_msg("open failed")); // handle error
	// close(cmd->redirects[0]);
	return (1);
}

int	here_doc(char *inp, t_cmd *cmd, int **docs)
{
	static int	count = 0;

	return (0);
}

// check errors (<<< <> <<>)
void	*in_redirect(char **table, t_cmd *cmd, int **docs)
{
	char	*file;

	(*table)++;
	if (**table == LEFT_REDIRECT)
	{
		(*table)++;
		// heredoc() TODO
		return (error_msg("TODO heredocs"));
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
