/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:17:27 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 18:04:20 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dispatch_builtin(t_cmd *cmd, t_save_struct *tstruct, int flag)
{
	if (!tstruct->cmd->cmd)
		return (-1);
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (ft_echo(cmd, &tstruct->envp, flag));
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (ft_export(cmd, &tstruct->envp, flag));
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (ft_exit(tstruct, &tstruct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (ft_unset(cmd->cmd, &tstruct->envp, tstruct));
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (ft_env(&tstruct->envp, cmd, flag));
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (ft_pwd(cmd->cmd, &tstruct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (ft_cd(tstruct));
	return (-1);
}

int	is_it_builtin(t_cmd *cmd, t_envp **env, t_save_struct *tstruct)
{
	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	ft_expand(cmd, env, tstruct);
	ft_get_path(cmd, tstruct);
	ft_remove_null_node(&cmd);
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (1);
	else
		return (0);
}
