#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		change_exit_code(1, 1);
	}
}

void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		change_exit_code(130, 1);
	}
}
void	handle_quit(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1,"Quit: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
		change_exit_code(131, TRUE);
	}
}

void	child_minishell_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		change_exit_code(1, 1);
	}
}
