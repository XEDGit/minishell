#ifndef ENV_H
# define ENV_H

# define B_INITSIZE 10
# define B_INCRSIZE 20

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
t_env	*env_create(char **envp);
t_env	*env_free(t_env *env);
char	*env_get(t_env *env, char *name, int mode);

#endif
