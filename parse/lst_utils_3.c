/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:35 by renard            #+#    #+#             */
/*   Updated: 2024/08/02 01:26:31 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lst_size(t_cmd *cmd)
{
	t_cmd	*save;
	int		i;

	i = 0;
	save = cmd;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	cmd = save;
	return (i);
}

void	ft_free_envp_lst(t_envp *lst, t_envp **env)
{
	t_envp	*temp;

	if (!lst)
		ft_free_envp_lst(*env, NULL);
	while (lst)
	{
		temp = lst->next;
		free(lst->var_name);
		free(lst->var_value);
		free(lst);
		lst = temp;
	}
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->redir);
		free(redir);
		redir = tmp;
	}
}

void	ft_free_node(t_cmd *node)
{
	if (node->cmd)
		ft_free_tab(node->cmd);
	free(node->path);
	free(node->exp_code);
	free(node);
}

void	ft_free_lst(t_cmd *lst)
{
	t_cmd	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->redir)
			ft_free_redir(lst->redir);
		ft_free_node(lst);
		lst = temp;
	}
}
