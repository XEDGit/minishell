/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:11:28 by lmuzio            #+#    #+#             */
/*   Updated: 2022/08/01 16:11:29 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBC_H
# define FT_LIBC_H

# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>

char	**ft_split(char const *s, char *c);
int		ft_strjoin(char **s1, char const *s2);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strchr(char *str, char key);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strclen_no_quotes(const char *start, const char *end);
size_t	ft_strclen(const char *start, const char *end);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strexcmp(const char *s1, const char *s2, size_t n, const char *del);
int		ft_isspace(int str);
char	**strsplit(char *s, char c);

#endif
