/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:38:24 by lmuzio            #+#    #+#             */
/*   Updated: 2023/05/29 15:45:23 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <env.h>

typedef struct s_file
{
	char			*name;
	int				here;
	int				dest;
	int				flags;
	int				mode;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				redirects[3];
	int				is_pipe;
	int				depth;
	int				depth_next;
	int				conditional;
	t_file			*files;
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
	t_env	*env;
	t_env	*aliases;
}	t_data;

// t_cmd library
t_cmd	*add_cmd(t_cmd **start);
int		free_cmds(t_cmd *start, char **tables, int exit_code);
int		debug_cmds(t_cmd *start);

#endif
