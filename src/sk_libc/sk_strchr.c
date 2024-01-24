/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:09:25 by lmuzio            #+#    #+#             */
/*   Updated: 2022/08/01 16:09:26 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*sk_strchr(char *s, int c)
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

char	*sk_strchr_skip_parentheses(char *s, int c)
{
	int		i;
	int		par;
	char	chr;

	i = 0;
	par = 0;
	chr = (char)c;
	while ((s[i] && s[i] != chr) || par > 0)
	{
		if (s[i] == '(')
			par++;
		else if (s[i] == ')')
			par--;
		i++;
	}
	if (s[i] != chr)
		return (0);
	return ((char *)(s + i));
}