/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:25 by renard            #+#    #+#             */
/*   Updated: 2024/07/29 12:58:43 by melmarti         ###   ########.fr       */
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
		exit(131);
	}
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
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

int	ft_tokenize(char *buffer, t_save_struct *t_struct, t_envp **env)
{
	t_cmd	*curr;
	int		bool_bracket;

	bool_bracket = 0;
	t_struct->envp = *env;
	if (ft_quote_len(buffer, ft_strlen(buffer)) == -1)
	{
		ft_putstr_fd("Minishell: Quote not valid\n", 2);
		return (-1);
	}
	ft_create_token_lst(buffer, t_struct);
	curr = t_struct->cmd;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	ft_remove_null_node(&(t_struct->cmd));
	ft_clean_cmd_lst(&(t_struct->cmd), t_struct);
	ft_wildcard(&(t_struct->cmd));
	if (ft_exec_syntax_functions(&(t_struct->cmd), &(t_struct->envp),
			t_struct) == -1 || !t_struct->cmd)
		return (-1);
	ft_return_code(ft_itoa(g_exit_status), env);
	return (0);
}
