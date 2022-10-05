#include <shared.h>

t_buffvar	*buff_free(t_buffvar *buff)
{
	free2d(buff->mem, buff->index - 1);
	free(buff);
	return (0);
}

/**
 * Returns index of buff, if there are no occurencies returns -1.
 * offset is the skippable length in buff[index] to get the content of var.
*/
int	buff_contains(t_buffvar *buff, char *to_find, size_t *offset)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (i < buff->index)
	{
		n = ft_strchr(buff->mem[i], '=') - buff->mem[i];
		if (!ft_strncmp(buff->mem[i], to_find, n) && \
		!ft_strncmp(buff->mem[i], to_find, ft_strlen(to_find)))
		{
			if (offset)
				*offset = n + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

/**
 * Checks available space in buff.
 * If no space left returns a mem copy with B_INCRSIZE more slots.
*/
t_buffvar	*buff_checker(t_buffvar *buff)
{
	int		i;
	char	**new_mem;

	if (buff->index < (buff->size - 1))
		return (buff);
	buff->size += B_INCRSIZE;
	new_mem = malloc(sizeof(char *) * buff->size);
	if (!new_mem)
		return (0);
	i = 0;
	while (i < buff->index)
	{
		new_mem[i] = buff->mem[i];
		i++;
	}
	free(buff->mem);
	buff->mem = new_mem;
	return (buff);
}

t_buffvar	*buff_copy(t_buffvar *buff, char **envp)
{
	int	len;

	while (envp && envp[buff->index])
	{
		len = ft_strlen(envp[buff->index]) + 1;
		buff->mem[buff->index] = malloc(sizeof(char) * len);
		if (!buff->mem[buff->index])
		{
			free2d(buff->mem, buff->index - 1);
			return (error_msg("Error: enviromental variable allocation\n", -1));
		}
		ft_strlcpy(buff->mem[buff->index], envp[buff->index], len);
		buff->index++;
	}
	buff->mem[buff->index] = 0;
	return (buff);
}

t_buffvar	*buff_create(char **envp)
{
	int			i;
	t_buffvar	*buff;

	buff = malloc(sizeof(t_buffvar));
	if (!buff)
		return (0);
	i = 0;
	buff->index = i;
	buff->size = B_INITSIZE;
	while (envp && envp[i])
		i++;
	while (buff->size <= i)
		buff->size += B_INCRSIZE;
	buff->mem = malloc(sizeof(char *) * buff->size);
	if (!buff->mem)
		return (0);
	buff->mem[buff->size - 1] = 0;// not necessary but can avoid future bugs
	if (!buff_copy(buff, envp))
		return (0);
	return (buff);
}
