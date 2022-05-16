/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:28:48 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/16 16:43:53 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_decimal(int n, int *c, int fd)
{
	if (n == 0)
		return (ft_string("0", c, fd));
	if (n == -2147483648)
		return (ft_string("-2147483648", c, fd));
	else if (n < 0)
	{
		ft_string("-", c, fd);
		n *= -1;
	}
	if (n >= 1)
	{
		if (n / 10 != 0)
			ft_decimal(n / 10, c, fd);
		ft_char(n % 10 + '0', c, fd);
	}
	return ;
}

void	ft_unsigned(unsigned int n, int *c, int fd)
{
	if (!n)
		return (ft_string("0", c, fd));
	if (n >= 1)
	{
		if (n / 10 != 0)
			ft_unsigned(n / 10, c, fd);
		ft_char(n % 10 + '0', c, fd);
	}
}

void	ft_hexazero(unsigned long long n, int options, int fd, int *c)
{
	ft_hexadecimal(n, options, fd, c);
	if (n == 0)
		ft_string("0", c, fd);
}

void	ft_hexadecimal(unsigned long long n, int options, int fd, int *c)
{
	int	rem;

	if (!n)
	{
		if (options % 2)
		{
			if (options == 1)
				ft_string("0X", c, fd);
			else
				ft_string("0x", c, fd);
		}
		return ;
	}
	ft_hexadecimal(n / 16, options, fd, c);
	rem = n % 16 + 48;
	if (rem < 58)
		ft_char(rem, c, fd);
	else if (options >= 32)
		ft_char(rem + 39, c, fd);
	else
		ft_char(rem + 7, c, fd);
	return ;
}
