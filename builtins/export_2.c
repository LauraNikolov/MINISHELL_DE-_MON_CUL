/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:04:50 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 18:24:48 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_envp **env, int fd)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(curr->var_name, fd);
		if (curr->var_value)
		{
			write(fd, "=\"", 3);
			ft_putstr_fd(curr->var_value, fd);
			write(fd, "\"", 2);
		}
		else if (curr->print_flag && !curr->var_value)
			write(fd, "=\"\"", 4);
		write(fd, "\n", 2);
		curr = curr->next;
	}
}

int	ft_export(t_cmd *node, t_envp **env, int flag)
{
	int		i;
	int		fd;
	char	**var;

	fd = -1;
	var = node->cmd;
	if (!env || !*var)
		return (0);
	if (!var[1])
		return (ft_fork_export(env, fd, flag, node));
	i = 1;
	while (var[i])
	{
		if (ft_handle_export_err(var[i]))
			return (ft_return_code(ft_strdup("1"), env));
		else
			ft_compare_var(env, var[i]);
		i++;
	}
	return (ft_return_code(ft_strdup("0"), env));
}
