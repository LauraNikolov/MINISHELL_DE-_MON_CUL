/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:04:50 by melmarti          #+#    #+#             */
/*   Updated: 2024/07/29 14:04:51 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_envp **env)
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
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->var_name, 1);
		if (curr->var_value)
		{
			write(1, "=\"", 3);
			ft_putstr_fd(curr->var_value, 1);
			write(1, "\"", 2);
		}
		else if (curr->print_flag && !curr->var_value)
			write(1, "=\"\"", 4);
		write(1, "\n", 2);
		curr = curr->next;
	}
}

int	ft_export(t_cmd *node, t_envp **env)
{
	int		i;
	char	**var;

	var = node->cmd;
	if (!env || !*var)
		return (0);
	if (!var[1])
		return (ft_fork_export(env));
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
