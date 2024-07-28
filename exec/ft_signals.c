#include "../minishell.h"

void	ft_handler_signals(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		write(1, "minishell : ", 13);
	}
}

void	ft_handler_child_signals(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		exit(131);
	}
	if (signal == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	ft_signal(int pid)
{
	if (pid != 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_signals);
	}
	else
	{
		signal(SIGQUIT, ft_handler_child_signals);
		signal(SIGINT, ft_handler_child_signals);
	}
}
