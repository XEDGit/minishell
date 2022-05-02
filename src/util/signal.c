#include <minishell.h>

static void	signals_handler(int code)
{
	if (code == SIGINT)
	{
		printf("\33[2K");
	    rl_on_new_line();
	    rl_redisplay();
		printf("\n");
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
	}
	return ;
}

int	signals_handler_setup(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, 0);
	return (0);
}
