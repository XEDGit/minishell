#include <parser.h>

static int	set_output_fd(t_cmd *cmd, char *file, int open_flags)
{
	if (cmd->redirects[1] != STDOUT_FILENO)
	{
		if (close(cmd->redirects[1]) == ERROR)
			return (error_int("Close error", 0));
	}
	cmd->redirects[1] = open(file, open_flags, MODE);
	free(file);
	if (cmd->redirects[1] == ERROR)
		return (error_int("Open error", 0)); // handle precise error
	return (1);
}

void	*out_redirect(char **table, t_cmd *cmd)
{
	int		flags;
	char	*file;

	(*table)++;
	if (**table == RIGHT_REDIRECT)
	{
		(*table)++;
		if (**table == LEFT_REDIRECT || **table == RIGHT_REDIRECT)
			return (0);
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
	{
		if (**table == LEFT_REDIRECT)
			return (0);
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	}
	file = get_filename(table);
	if (file && set_output_fd(cmd, file, flags))
		return ((void *) 1);
	return (error_msg("Rx redirect failed"));
}
