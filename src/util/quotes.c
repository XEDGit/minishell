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

int	clean_cmd_quotes(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
		erase_chars(cmd->args[i++], "\'\"");
	cmd->cmd = cmd->args[0];
	return (true);
}
