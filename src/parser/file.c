#include <parser.h>

// Retrive and expand the redirect word(filename)
// TODO handle edge cases
char    *get_filename(char **input)
{
    char    *tmp;
    char    *name;
	int		len;

	len = 0;
    while (ft_isspace(**input))
        (*input)++;
	tmp = *input;
	while (*tmp && !ft_isspace(*tmp++))// check other metachars
		len++;
	tmp = malloc(sizeof(char) * (++len));
	if (!tmp)
		return ((char *) error_msg("Malloc failed"));
	ft_strlcpy(tmp, *input, len);
	*input += len - 1;
	name = remove_quotes(tmp);
	free(tmp);
	if (!name)
		return ((char *) error_msg("Remove quotes failed"));
    return (name);
}
