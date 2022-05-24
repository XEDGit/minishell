#include <parser.h>

// pass only file name -> avoid expanding input everytime
int right_rdrt(char *file, t_cmd *cmd)
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

int append(char *file, t_cmd *cmd)
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
