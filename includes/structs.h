/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:38:24 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 18:51:36 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				redirects[3];
	int				is_pipe;
	int				depth;
	int				depth_next;
	int				conditional;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmds;
	int		**heredocs;
	int		heredoc_c;
	char	*input;
	char	**paths;
}	t_data;

// t_cmd library
t_cmd	*add_cmd(t_cmd **start);
int		free_cmds(t_cmd *start, char **tables, int exit_code);
int		debug_cmds(t_cmd *start);

#endif