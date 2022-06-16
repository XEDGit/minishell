#include <parser.h>

int	is_del(char c)
{
	if (c == ' ' || c == '$' || c == '<' || c == '>' \
		|| c == '&' || c == '|')
		return (1);
	return (0);
}

t_var	*get_var_name(t_var *res, char *str)
{
	res->length = 0;
	res->p = str;
	while (str[res->length] && !is_del(str[res->length]))
		res->length++;
	// if (!res->length)
	// 	return (0);
	res->c = str[res->length];
	ft_memset(str + res->length, '\0', 1);
	return (res);
}

int	var_name_length(char *str)
{
	int	len;

	len = 0;
	while (*str && !is_del(*str++))
		len++;
	return (len);
}
