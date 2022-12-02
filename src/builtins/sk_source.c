#include <shared.h>

int sk_source(t_cmd *cmd, t_data *data)
{
    char	*path, *buff_ptr;
	char	buff[1001];
	int		read_ret, err = 0;

    if (!cmd->args[1])
        return (error_int("filename argument is required", "source", -1, 1));
    path = cmd->args[1];
    if (!access(path, F_OK) && !access(path, R_OK))
	{
		int fd = open(path, O_RDONLY);
		if (fd == -1)
			return (1);
		read_ret = 1;
		while (read_ret)
		{
			read_ret = read(fd, &buff, 1000);
			if (read_ret >= 0)
				buff[read_ret] = 0;
			else
				continue;
			buff_ptr = &buff[0];
			while ((path = sk_strchr(buff_ptr, '\n')))
			{
				*path = 0;
				lexer(buff_ptr, data->env, data->aliases);
				buff_ptr = path + sizeof(char);
			}
			if (buff_ptr != &buff[read_ret])
				lexer(buff_ptr, data->env, data->aliases);
		}
		if (read_ret == -1)
			err = error_int("Error reading file", "source", -1, 1);
		close(fd);
	}
    else
        err = error_int("File not found or not readable", "source", -1, 1);
	return (err);
}