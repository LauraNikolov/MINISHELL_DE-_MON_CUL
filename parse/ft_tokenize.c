/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:25 by renard            #+#    #+#             */
/*   Updated: 2024/07/29 00:37:32 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tokenize(char *buffer, save_struct *t_struct, t_envp **env)
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
	return (0);
}
