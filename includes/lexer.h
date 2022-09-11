/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:25:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/11 18:35:39 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <shared.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

int		dchar_check(char *input, char ch);
char	*find_next_char(char *start);
int		semicolon_check(char *input);
int		pipe_check(char *input);
int		lexer_multiline_check(char *in, int delimiter);
int		parenthesis_check(char *input);
int		heredoc_check(char *input, t_data *data);
int		heredoc_repeat(char *input, int *fds);
char	*extract_pipe(int fd);
char	*remove_quotes(char *input);
int		skip_quotes(char *input);
int		is_open(char c);
int		syntax_check(char *input, t_data *data);
int		check_double_commands(char *str, int c, int diff);

#endif
