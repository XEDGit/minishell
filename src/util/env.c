#include <ft_libc.h>

//	Returns 0 on error or value of variable
char    *ft_get_env(char **vars, char *name)
{
        size_t  n;
        char    *out;

        while (*vars)
        {
                n = ft_strchr(*vars, '=') - *vars;
                if (!ft_strncmp(*vars, name, n))
		{
			n++;
			out = malloc(sizeof(char) * ft_strlen(*vars + n) + 1);
			if (out)
				ft_strlcpy(out, *vars + n, ft_strlen(*vars + n) + 1);
			return (out);
		}
                vars++;
        }
	out = malloc(sizeof(char));
	if (out)
		*out = 0;
        return (out);
}
