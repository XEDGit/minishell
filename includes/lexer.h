/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:25:56 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/15 15:20:32 by nmolinel         ###   ########.fr       */
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
int		io_check(char *input);
int		semicolon_check(char *input);
int		pipe_check(char *input);
int		multiline_handle(t_data *data, char *input, int c, bool save_history);
int		lexer_multiline_check(char *in, int delimiter);
int		repeat_readline(char **buffer, char delimiter, t_data *data);
int		parenthesis_check(char *input);
int		heredoc_check(char *input, t_data *data);
int		heredoc_repeat(char *input, int *fds);
char	*extract_pipe(int fd);
char	*remove_quotes(char *input);
int		skip_quotes(char *input);
int		is_open(char c);
int		truncate_delimiter(char *del);
int		syntax_check(char *input, t_data *data);
int		check_double_commands(char *str, int c, int diff);
bool	check_standalone_redirects(char *input);

#endif
