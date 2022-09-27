/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 18:52:41 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 19:12:29 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

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
	int		c;
	char	ch;
	char	*res;

	c = 0;
	ch = 0;
	res = ft_strdup(input);
	while (res && res[c] && res[c] != ' ')
	{
		if (res[c] == SINGLE_QUOTE || res[c] == DOUBLE_QUOTE)
		{
			if (!ch)
				ch = res[c];
			else
				ch = 0;
			ft_strlcpy(res + c, res + c + 1, ft_strlen(res + c));
		}
		else if (!ch && (res[c] == '<' || res[c] == '>'))
			res[c] = 0;
		else
			c++;
	}
	return (res);
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

int	clean_quotes(t_cmd *cmd)
{
	int		i;
	char	*p;

	i = 0;
	while (cmd->args[i])
	{
		p = remove_quotes(cmd->args[i]);
		if (!p)
			return (false);
		free(cmd->args[i]);
		cmd->args[i++] = p;
	}
	cmd->cmd = cmd->args[0];
	return (true);
}
