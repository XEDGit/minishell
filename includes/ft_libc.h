#ifndef FT_LIBC_H
# define FT_LIBC_H

char	**ft_split(char const *s, char *c);
int		ft_strjoin(char **s1, char const *s2);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strclen_no_quotes(const char *start, const char *end);
size_t	ft_strclen(const char *start, const char *end);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strexcmp(const char *s1, const char *s2, size_t n, const char *del);
int		ft_isspace(int str);
char	**strsplit(char const *s, char c);

#endif
