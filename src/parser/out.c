#include <parser.h>

// TODO: merge right and append funcs
static int right_rdrt(char *file, t_cmd *cmd)
{
    if (cmd->redirects[1] != STDOUT_FILENO)
        close(cmd->redirects[1]); // handle error
    cmd->redirects[1] = open(file, O_WRONLY | O_CREAT, MODE);
    free(file);
    if (cmd->redirects[1] == ERROR)
        return (0); // handle error
    // close(cmd->redirects[1]); // 
    return (1);
}

static int append(char *file, t_cmd *cmd)
{
    if (cmd->redirects[1] != STDOUT_FILENO)
        close(cmd->redirects[1]); // handle error
    cmd->redirects[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, MODE);
    free(file);
    if (cmd->redirects[1] == ERROR)
        return (0); // handle error
    // close(cmd->redirects[1]);
    return (1);
}

void	*out_redirect(char **table, t_cmd *cmd)
{
	char	*file;

	(*table)++;
	if (**table == RIGHT_REDIRECT)
	{
		(*table)++;
		file = get_filename(table);
		if (!file)
			return (error_msg("File name failed")); // error
		if (!append(file, cmd))
			return (error_msg("Append failed")); // append error
	}
	else
	{
		file = get_filename(table);
		if (!file)
			return (error_msg("File name failed")); // error
		if (!right_rdrt(file, cmd))
			return (error_msg("Right redirect failed")); // right redirect error
	}
	return ((void *) 1);
}
