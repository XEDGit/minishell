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

int	here_doc(char *inp, t_cmd *cmd, int ** docs)
{
	static int	count = 0;

	return (0);
}
