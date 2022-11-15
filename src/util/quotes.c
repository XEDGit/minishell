/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:52:41 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/15 16:42:09 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

char	*remove_quotes_pt2(char *p, int i);
int		truncate_delimiter(char *del );

/*
* This function is to use inside a loop
* Returns false (0) if outside unclosed quotes,
* otherwise if c is ' or " returns the corresponding ascii value,
* call is_open(-1) to reset open 
*/
int	is_open(char c)
{
	static int	open = 0;

	if (!open && c == SINGLE_QUOTE)
		open = SINGLE_QUOTE;
	else if (!open && c == DOUBLE_QUOTE)
		open = DOUBLE_QUOTE;
	else if (open == SINGLE_QUOTE && c == SINGLE_QUOTE)
		open = false;
	else if (open == DOUBLE_QUOTE && c == DOUBLE_QUOTE)
		open = false;
	else if (c == -1)
		open = false;
	return (open);
}

char	*remove_quotes(char *input)
{
	char	*p;
	int		open;
	int		i;

	while (*input == ' ')
		input++;
	if (!*input)
		return (0);
	p = malloc(sizeof(char) * (ft_strlen(input) + 1));
	i = 0;
	while (p && *input)
	{
		open = is_open(*input);
		if ((!open && *input != '\'' && *input != '\"') \
		|| (open && *input != open))
			p[i++] = *input++;
		else
		{
			input++;
			continue ;
		}
		if (!open && i > 0 && truncate_delimiter(&p[i - 1]))
			break ;
	}
	return (remove_quotes_pt2(p, i));
}

int	skip_quotes(char *input)
{
	char	ch;
	int		c;

	c = 0;
	if (input[c] != DOUBLE_QUOTE && input[c] != SINGLE_QUOTE)
		return (0);
	ch = input[c++];
	while (input[c] && input[c] != ch)
		c++;
	if (!input[c])
		c--;
	return (c);
}

char	*quotes_del(char *str)
{
	char	*p;
	int		open;
	int		i;

	p = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!p)
		return (false);
	i = 0;
	while (*str)
	{
		open = is_open(*str);
		if (!open && (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE))
			str++;
		else if (!open || (open && *str != open))
			p[i++] = *str++;
		else
			str++;
	}
	if (open)
		is_open(-1);
	p[i] = 0;
	return (p);
}

int	clean_quotes(t_cmd *cmd)
{
	int		i;
	char	*p;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strlen(cmd->args[i]) == 2 && !ft_strcmp(cmd->args[i], "\"\""))
			p = ft_strdup("");
		else
			p = quotes_del(cmd->args[i]);
		if (!p)
			return (false);
		free(cmd->args[i]);
		cmd->args[i++] = p;
	}
	cmd->cmd = cmd->args[0];
	return (true);
}
