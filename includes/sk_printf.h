/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:04:14 by lmuzio            #+#    #+#             */
/*   Updated: 2023/05/29 15:45:26 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SK_PRINTF_H
# define SK_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

# define LOWCASE 32

int		sk_printf(const char *str, ...);
int		sk_dprintf(int fd, const char *str, ...);
int	sk_decimal(int n, int *c, int fd);
void	sk_hexadecimal(unsigned long long n, int options, int fd, int *c);
void	sk_hexazero(unsigned long long n, int options, int fd, int *c);
void	sk_string(char *str, int *c, int fd);
void	sk_char(char ch, int *c, int fd);
int		sk_unsigned(unsigned int n, int *c, int fd);

#endif
