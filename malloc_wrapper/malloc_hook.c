/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_hook.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/14 22:15:23 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/14 22:15:27 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#include <dlfcn.h>
#include <execinfo.h>
#include <stdio.h>

int	malloc_hook_backtrace_readable(char ***stack_readable)
{
	void	*stack[10];
	int		stack_size;

	stack_size = backtrace(stack, 10);
	*stack_readable = backtrace_symbols(stack, stack_size);
	return (stack_size);
}

void	malloc_hook_string_edit(char *str)
{
	str = &str[59];
	while (*str && *str != ' ')
		str++;
	*str = 0;
}

void	*malloc(size_t size)
{
	void	*ret;
	char	**stack;
	int		stack_size;
	void	(*og_free)(void *);
	void	*(*og_malloc)(size_t);

	og_malloc = dlsym(RTLD_NEXT, "malloc");
	og_free = dlsym(RTLD_NEXT, "free");
	ret = og_malloc(size);
	stack_size = malloc_hook_backtrace_readable(&stack);
	malloc_hook_string_edit(stack[2]);
	malloc_hook_string_edit(stack[3]);
	printf("(MALLOC_WRAPPER) %s - %s allocated %zu bytes at %p\n", \
	&stack[3][59], &stack[2][59], size, ret);
	og_free(stack);
	return (ret);
}

void	free(void *tofree)
{
	char	**stack;
	void	(*og_free)(void *);

	og_free = dlsym(RTLD_NEXT, "free");
	malloc_hook_backtrace_readable(&stack);
	malloc_hook_string_edit(stack[2]);
	malloc_hook_string_edit(stack[3]);
	printf("(FREE_WRAPPER) %s/%s free %p\n", \
	&stack[3][59], &stack[2][59], tofree);
	og_free(stack);
	og_free(tofree);
}
