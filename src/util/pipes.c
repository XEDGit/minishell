#include <minishell.h>

char    *ft_realloc(char *src, unsigned int size)
{
    char    *res;

    res = malloc((size + 1) * sizeof(char));
    ft_strlcpy(res, src, ft_strlen(src) + 1);
    free(src);
    return (res);
}

char    *extract_pipe(int fd)
{
    char    *buffer;
    int     buffer_size;
    int     size_mult;
    int     c;

    c = 0;
    size_mult = 1;
    buffer_size = 10;
    buffer = malloc((buffer_size + 1) * sizeof(char));
    while (1)
    {
        if (read(fd, &buffer[(size_mult - 1) * buffer_size + c], 1) < 1)
            break ;
        buffer[(size_mult - 1) * buffer_size + c + 1] = 0;
        if (++c == buffer_size)
        {
            c = 0;
            buffer = ft_realloc(buffer, buffer_size * ++size_mult);
        }
    }
    return (buffer);
}