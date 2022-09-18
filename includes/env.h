/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:31:48 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:31:48 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

# define B_INITSIZE 30
# define B_INCRSIZE 60

typedef struct s_buffvar
{
	int		index;
	int		size;
	char	**mem;
}	t_buffvar;

typedef struct s_env
{
	t_buffvar	*envp;
	t_buffvar	*envl;
}	t_env;

//	buff
t_buffvar	*buff_create(char **envp);
t_buffvar	*buff_free(t_buffvar *buff);
t_buffvar	*buff_checker(t_buffvar *buff);
int			buff_contains(t_buffvar *buff, char *to_find, size_t *offset);

//	env
t_env		*env_setup(char **envp);
t_env		*env_create(char **envp);
t_env		*env_free(t_env *env);
char		*env_get(t_env *env, char *name, int mode);
t_env		*env_add(t_env *env, char *var, int mode);
t_env		*env_remove(t_env *env, char *var, int mode);
char		*build_var(char *name, char *value);

#endif
