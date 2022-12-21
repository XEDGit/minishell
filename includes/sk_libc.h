/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_libc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:11:28 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/17 14:35:03 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SK_LIBC_H
# define SK_LIBC_H

# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>

void	*sk_memcpy(void *to_write, void *to_copy, size_t len);
void	*sk_memset(void *b, int c, size_t len);
int		sk_isdigit(char ch);
char	**sk_split(char const *s, char *c);
int		sk_strjoin(char **s1, char const *s2, int free_s2);
char	*sk_strdup(const char *s1);
char	*sk_strchr(char *str, char key);
size_t	sk_strlcat(char *dst, const char *src, size_t dstsize);
size_t	sk_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	sk_strclen_no_quotes(const char *start, const char *end);
size_t	sk_strclen(const char *start, const char *end);
size_t	sk_strlen(const char *str);
int		sk_strcmp(const char *s1, const char *s2);
int		sk_strncmp(const char *s1, const char *s2, size_t n);
int		sk_strexcmp(const char *s1, const char *s2, size_t n);
char	*sk_strnstr(const char *haystack, const char *needle, unsigned int len);
int		sk_isspace(int str);
long	sk_atoi(const char *str);
int		sk_strisspace(char *str);
char	*sk_itoa(int n);
char	**strsplit(char *s, char c);

#endif
