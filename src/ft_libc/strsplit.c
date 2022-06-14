#include <ft_libc.h>

static int	count_size(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || !*(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static char	**split(char **arr, char *s, char del)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (*s)
	{
		while (*s == del)
			s++;
		while (s[count] && s[count] != del)
			count++;
		if (count)
		{
			arr[index++] = s;
			ft_memset(s + count, '\0', 1);
			s = s + count + 1;
			count = 0;
		}
	}
	arr[index] = 0;
	return (arr);
}

char	**strsplit(char *s, char c)
{
	char	**arr;
	int		size;


	size = count_size(s, c);
	if (!size)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (0);
	return (split(arr, s, c));
}
