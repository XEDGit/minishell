/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:04:14 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/25 20:41:31 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

# define LOWCASE 32

int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
void	ft_decimal(int n, int *c, int fd);
void	ft_hexadecimal(unsigned long long n, int options, int fd, int *c);
void	ft_hexazero(unsigned long long n, int options, int fd, int *c);
void	ft_string(char *str, int *c, int fd);
void	ft_char(char ch, int *c, int fd);
void	ft_unsigned(unsigned int n, int *c, int fd);

#endif