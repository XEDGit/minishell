/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:04:19 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/25 20:41:58 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sk_printf.h"

void	sk_string(char *str, int *c, int fd)
{
	int		cont;

	cont = 0;
	if (str)
	{
		while (str[cont])
			cont++;
		write(fd, str, cont);
	}
	else
		sk_string("(null)", c, fd);
	c += cont;
}

void	sk_char(char ch, int *c, int fd)
{
	write(fd, &ch, 1);
	*c += 1;
}

char	*sk_check_flag(char *str, int *c, int fd, va_list *args)
{
	if (*str == '%')
		sk_string("%", c, fd);
	else if (*str == 'c')
		sk_char((char)va_arg(*args, int), c, fd);
	else if (*str == 's')
		sk_string(va_arg(*args, char *), c, fd);
	else if (*str == 'p')
		sk_hexazero(va_arg(*args, unsigned long long), LOWCASE + 1, fd, c);
	else if (*str == 'd' || *str == 'i')
		sk_decimal(va_arg(*args, long), c, fd);
	else if (*str == 'u')
		sk_unsigned(va_arg(*args, unsigned int), c, fd);
	else if (*str == 'x')
		sk_hexazero(va_arg(*args, unsigned int), LOWCASE, fd, c);
	else if (*str == 'X')
		sk_hexazero(va_arg(*args, unsigned int), 0, fd, c);
	return (str);
}

int	sk_printf(const char *str, ...)
{
	va_list	args;
	int		c;

	va_start(args, str);
	c = 0;
	while (*str)
	{
		if (*str == '%')
			str = sk_check_flag((char *)str + 1, &c, 1, &args);
		else
			c += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (c);
}

int	sk_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		c;

	va_start(args, str);
	c = 0;
	while (*str)
	{
		if (*str == '%')
			str = sk_check_flag((char *)str + 1, &c, fd, &args);
		else
			c += write(fd, str, 1);
		str++;
	}
	va_end(args);
	return (c);
}
