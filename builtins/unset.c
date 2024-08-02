/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:04 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 11:14:58 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_envp_node(t_envp *node)
{
	free(node->var_name);
	free(node->var_value);
	free(node);
}

static void	ft_link_var(t_envp *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	ft_free_envp_node(node);
}

static void	ft_remove_var(t_envp *curr, t_envp **env, t_save_struct *tstruct)
{
	tstruct->envp = tstruct->envp->next;
	*env = curr->next;
	ft_free_envp_node(curr);
	if (*env)
		(*env)->prev = NULL;
}

int	ft_unset(char **var, t_envp **env, t_save_struct *tstruct)
{
	t_envp	*curr;
	t_envp	*temp;
	int		i;

	curr = *env;
	while (curr)
	{
		i = -1;
		temp = curr->next;
		while (var[++i])
		{
			if (!ft_strcmp(curr->var_name, var[i]))
			{
				if (curr == *env)
					ft_remove_var(curr, env, tstruct);
				else
					ft_link_var(curr);
				break ;
			}
		}
		curr = temp;
	}
	return (ft_return_code(ft_strdup("0"), env));
}
