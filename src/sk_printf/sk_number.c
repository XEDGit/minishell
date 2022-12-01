/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:28:48 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/16 16:43:53 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sk_printf.h"

void	sk_decimal(int n, int *c, int fd)
{
	if (n == 0)
		return (sk_string("0", c, fd));
	if (n == -2147483648)
		return (sk_string("-2147483648", c, fd));
	else if (n < 0)
	{
		sk_string("-", c, fd);
		n *= -1;
	}
	if (n >= 1)
	{
		if (n / 10 != 0)
			sk_decimal(n / 10, c, fd);
		sk_char(n % 10 + '0', c, fd);
	}
	return ;
}

void	sk_unsigned(unsigned int n, int *c, int fd)
{
	if (!n)
		return (sk_string("0", c, fd));
	if (n >= 1)
	{
		if (n / 10 != 0)
			sk_unsigned(n / 10, c, fd);
		sk_char(n % 10 + '0', c, fd);
	}
}

void	sk_hexazero(unsigned long long n, int options, int fd, int *c)
{
	sk_hexadecimal(n, options, fd, c);
	if (n == 0)
		sk_string("0", c, fd);
}

void	sk_hexadecimal(unsigned long long n, int options, int fd, int *c)
{
	int	rem;

	if (!n)
	{
		if (options % 2)
		{
			if (options == 1)
				sk_string("0X", c, fd);
			else
				sk_string("0x", c, fd);
		}
		return ;
	}
	sk_hexadecimal(n / 16, options, fd, c);
	rem = n % 16 + 48;
	if (rem < 58)
		sk_char(rem, c, fd);
	else if (options >= 32)
		sk_char(rem + 39, c, fd);
	else
		sk_char(rem + 7, c, fd);
	return ;
}
