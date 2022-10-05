/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:38:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/10/05 13:38:56 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}
