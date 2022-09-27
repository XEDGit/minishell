#include <parser.h>

static int	set_output_fd(t_cmd *cmd, char *file, int open_flags)
{
	if (cmd->redirects[1] != STDOUT_FILENO)
	{
		if (close(cmd->redirects[1]) == ERROR)
			return (error_int("Close file descriptor error", cmd->cmd, 1, 0));
	}
	cmd->redirects[1] = open(file, open_flags, MODE);
	free(file);
	if (cmd->redirects[1] == ERROR)
		return (error_int("Open file descriptor error", cmd->cmd, 1, 0));
	return (1);
}

void	*out_redirect(char **table, t_file *file)
{
	(*table)++;
	if (**table == RIGHT_REDIRECT)
	{
		(*table)++;
		file->flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
		file->flags = O_WRONLY | O_CREAT | O_TRUNC;
	file->name = get_filename(table);
	if (file->name)
		return ((void *) 1);
	return (error_msg("Rx redirect failed"));
}
