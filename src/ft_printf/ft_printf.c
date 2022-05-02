/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:04:19 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/25 20:41:58 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_string(char *str, int *c, int fd)
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
		ft_string("(null)", c, fd);
	c += cont;
}

void	ft_char(char ch, int *c, int fd)
{
	write(fd, &ch, 1);
	*c += 1;
}

char	*ft_check_flag(char *str, int *c, int fd, va_list *args)
{
	if (*str == '%')
		ft_string("%", c, fd);
	else if (*str == 'c')
		ft_char((char)va_arg(*args, int), c, fd);
	else if (*str == 's')
		ft_string(va_arg(*args, char *), c, fd);
	else if (*str == 'p')
		ft_hexazero(va_arg(*args, unsigned long long), LOWCASE + 1, fd, c);
	else if (*str == 'd' || *str == 'i')
		ft_decimal(va_arg(*args, long), c, fd);
	else if (*str == 'u')
		ft_unsigned(va_arg(*args, unsigned int), c, fd);
	else if (*str == 'x')
		ft_hexazero(va_arg(*args, unsigned int), LOWCASE, fd, c);
	else if (*str == 'X')
		ft_hexazero(va_arg(*args, unsigned int), 0, fd, c);
	return (str);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		c;

	va_start(args, str);
	c = 0;
	while (*str)
	{
		if (*str == '%')
			str = ft_check_flag((char *)str + 1, &c, 1, &args);
		else
			c += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (c);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		c;

	va_start(args, str);
	c = 0;
	while (*str)
	{
		if (*str == '%')
			str = ft_check_flag((char *)str + 1, &c, fd, &args);
		else
			c += write(fd, str, 1);
		str++;
	}
	va_end(args);
	return (c);
}
