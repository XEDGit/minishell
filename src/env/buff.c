#include <shared.h>

t_buffvar	*buff_free(t_buffvar *buff)
{
	free2d(buff->mem, buff->index - 1);
	free(buff);
	return (0);
}

// TODO add buff expander
t_buffvar	*buff_create(char **envp)
{
	int			i;
	int			len;
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
	while (envp && envp[buff->index])
	{
		len = ft_strlen(envp[buff->index]) + 1;
		buff->mem[buff->index] = malloc(sizeof(char) * len);
		if (!buff->mem[buff->index])
		{
			free2d(buff->mem, buff->index - 1);
			return (error_msg("Error: enviromental variable allocation\n"));
		}
		ft_strlcpy(buff->mem[buff->index], envp[buff->index], len);
		buff->index++;
	}
	return (buff);
}
