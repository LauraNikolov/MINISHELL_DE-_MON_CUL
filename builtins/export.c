/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:17:40 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 18:24:05 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_env(t_envp **env)
{
	t_envp	*curr;

	if (!env || !*env)
		return ;
	curr = *env;
	while (curr->next)
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_content(&curr->var_name, &curr->next->var_name);
			ft_swap_content(&curr->var_value, &curr->next->var_value);
			curr = *env;
		}
		else
			curr = curr->next;
	}
}

void	ft_add_var(int flag, char c, char *var, t_envp **env)
{
	if (!flag && c == '=')
		add_to_envp_lst(env, create_envp_node(var, 1));
	else if (!flag)
		add_to_envp_lst(env, create_envp_node(var, 0));
}

void	ft_compare_var(t_envp **env, char *var)
{
	t_envp	*curr;
	int		i;
	int		flag;

	flag = 0;
	i = ft_strchr(var, '=');
	if (i == -1)
		i = ft_strlen(var);
	curr = *env;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, var, i))
		{
			if ((size_t)i != ft_strlen(curr->var_name))
				break ;
			flag = 1;
			if (var[i] && var[i + 1])
				ft_override_content(&curr->var_value, &var[i + 1]);
			if (var[i] == '=')
				curr->print_flag = 1;
		}
		curr = curr->next;
	}
	ft_add_var(flag, var[i], var, env);
}

int	ft_fork_export(t_envp **env, int fd, int flag, t_cmd *node)
{
	pid_t	pid;

	ft_set_fd(flag, node, &fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_sort_env(env);
		ft_print_env(env, fd);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (fd != STDOUT_FILENO && flag)
			close(fd);
	}
	return (ft_return_code(ft_strdup("0"), env));
}

int	ft_handle_export_err(char *var)
{
	int	j;

	if (var[0] == '=')
	{
		ft_putstr_cmd_fd("Minishell : export: `", 2, NULL, 2);
		ft_putstr_cmd_fd(var, 2, NULL, 2);
		ft_putstr_cmd_fd("': not a valid identifier", 2, NULL, 0);
		return (1);
	}
	j = 0;
	while (var[j] && var[j] != '=')
	{
		if (var[j] == '-' || !ft_isalpha(var[0]))
		{
			ft_putstr_cmd_fd("Minishell : export: `", 2, NULL, 2);
			ft_putstr_cmd_fd(var, 2, NULL, 2);
			ft_putstr_cmd_fd("': not a valid identifier", 2, NULL, 0);
			return (1);
		}
		j++;
	}
	return (0);
}
