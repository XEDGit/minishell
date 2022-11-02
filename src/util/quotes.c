/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 18:52:41 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 17:45:21 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

char	*remove_quotes_pt2(char *p, int i, int open);

/*
* This function is to use inside a loop
* Returns true (0) if inside unclosed quotes,
* otherwise if c is ' or " returns the corresponding ascii value 
*/
int	is_open(char c)
{
	static int	open;

	if (!open && c == SINGLE_QUOTE)
		open = SINGLE_QUOTE;
	else if (!open && c == DOUBLE_QUOTE)
		open = DOUBLE_QUOTE;
	else if (open == SINGLE_QUOTE && c == SINGLE_QUOTE)
		open = 0;
	else if (open == DOUBLE_QUOTE && c == DOUBLE_QUOTE)
		open = 0;
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
		if (*input == '<' || *input == '>')
			break ;
		open = is_open(*input);
		if (!open && (*input == SINGLE_QUOTE || *input == DOUBLE_QUOTE))
			input++;
		else if (!open || (open && *input != open))
			p[i++] = *input++;
		else
			input++;
	}
	return (remove_quotes_pt2(p, i, open));
}

int	skip_quotes(char *input)
{
	char	ch;
	char	*start;
	int		c;

	c = 0;
	start = input;
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
