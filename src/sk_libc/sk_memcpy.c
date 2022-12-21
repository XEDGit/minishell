#include <stddef.h>

void	*sk_memcpy(void *to_write, void *to_copy, size_t len)
{
	unsigned char	*write, *copy;
	int				i;

	write = (unsigned char *) to_write;
	copy = (unsigned char *) to_copy;
	if (write == copy || !len)
		return (to_write + len);
	if (copy > write && copy < write + len)
	{
		i = len;
		while (--i >= 0)
			write[i] = copy[i];
		return (to_write + len);
	}
	i = -1;
	while (++i != len)
		write[i] = copy[i];
	return (to_write + i);
}