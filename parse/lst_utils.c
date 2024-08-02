/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:37 by renard            #+#    #+#             */
/*   Updated: 2024/08/02 18:03:09 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_envp_fd(t_envp **node, int fd)
{
	if (!*node)
		return ;
	if ((*node)->var_name)
	{
		ft_putstr_fd((*node)->var_name, fd);
		write(fd, "=", 1);
		if ((*node)->var_value)
			ft_putstr_fd((*node)->var_value, fd);
		write(fd, "\n", 1);
	}
}

int	ft_print_envp(t_envp **envp, t_cmd *node, int flag)
{
	t_envp	*curr;
	int		fd;

	fd = -1;
	ft_set_fd(flag, node, &fd);
	curr = *envp;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
		if (fd >= 0)
			ft_print_envp_fd(&curr, fd);
		curr = curr->next;
	}
	if (fd != STDOUT_FILENO && flag)
		close(fd);
	return (0);
}

t_cmd	*lst_last(t_cmd *node)
{
	t_cmd	*curr;

	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_redir	*lst_last_redir(t_redir *node)
{
	t_redir	*curr;

	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_envp	*lst_envp_last(t_envp *node)
{
	t_envp	*curr;

	if (!node)
		return (NULL);
	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}
