#include <parser.h>

//	Correct order:
//	- tilde expansion
//	- variable expansion
//	- * pattern
int	expander(char **tables, t_env *env)
{
	if (!ft_tilde_expand(tables, env) || \
		!vars_expansion(tables, env))
		return (false);
	// wildcard TODO
	return (true);
}
