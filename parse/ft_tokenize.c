/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:25 by renard            #+#    #+#             */
/*   Updated: 2024/07/29 15:00:06 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status;

void	ft_handler_signals(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handler_child_signals(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_status = 131;
	}
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
}

void	ft_signal(int pid)
{
	if (pid == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_signals);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, ft_handler_child_signals);
		signal(SIGINT, ft_handler_child_signals);
	}
	else if(pid == 3)
		signal(SIGINT, SIG_IGN);
	else if (pid == 2)
		signal(SIGINT, SIG_DFL);
}

int	ft_tokenize(char *buffer, t_save_struct *tstruct, t_envp **env)
{
	t_cmd	*curr;
	int		bool_bracket;

	bool_bracket = 0;
	tstruct->envp = *env;
	if (ft_quote_len(buffer, ft_strlen(buffer)) == -1)
		return (ft_putstr_fd("Minishell: Quote not valid\n", 2), -1);
	ft_create_token_lst(buffer, tstruct);
	curr = tstruct->cmd;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	ft_remove_null_node(&(tstruct->cmd));
	ft_clean_cmd_lst(&(tstruct->cmd), tstruct);
	ft_wildcard(&(tstruct->cmd));
	if (ft_exec_syntax_functions(&(tstruct->cmd), &(tstruct->envp), tstruct) ==
		-1 || !tstruct->cmd)
		return (-1);
	if (g_exit_status != 0)
		ft_return_code(ft_itoa(g_exit_status), env);
	return (0);
}
