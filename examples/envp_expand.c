/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 03:16:45 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/23 08:06:51 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	chr;

	i = 0;
	chr = (char)c;
	while (s[i] && s[i] != chr)
		i++;
	if (s[i] != chr)
		return (0);
	return ((char *)(s + i));
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!s1)
		printf("dasdas\n");
	return 0;
	while ((*s1 || *s2) && n--)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*expand_var(char *key, char **envp)
{
	size_t	n;

	while (*envp)
	{
		n = ft_strchr(*envp, '=') - *envp;
		if (!ft_strncmp(key, *envp, n++))
			return (*envp + n);
		envp++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*var = expand_var(argv[1], envp);
	if (var)
		printf("%s\n", var);
	else
		printf("Error\n");
	exit(0);
}