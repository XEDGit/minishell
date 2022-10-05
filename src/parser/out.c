#include <parser.h>

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
	return (error_msg("Rx redirect failed", -1));
}
