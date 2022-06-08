#include <parser.h>

int	get_length(char *input)
{
	int		len;

	len = 0;
	while (input[len] && !ft_isspace(input[len]))
	{
		if (!is_open(input[len]) && (input[len] == '<' || input[len] == '>'))
			break ;
		len++;
	}
	return (len);
}

// Retrive and expand the redirect word(filename)
// TODO handle edge cases
char	*get_filename(char **input)
{
	char	*tmp;
	char	*name;
	int		len;

	while (ft_isspace(**input))
		(*input)++;
	tmp = *input;
	len = get_length(*input);
	if (!len)
		return ((char *) error_msg(""));
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
