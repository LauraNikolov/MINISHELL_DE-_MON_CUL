/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:05:37 by lnicolof          #+#    #+#             */
/*   Updated: 2024/08/02 09:25:13 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_for_child(t_cmd *cmd, int *return_value)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		*return_value = WEXITSTATUS(status);
	return (*return_value);
}

void	manage_single_child(t_cmd *cmd, char ***envp)
{
	if (apply_redir(cmd) == -1)
		exit(1);
	if (cmd->std_in != STDIN_FILENO)
	{
		dup2(cmd->std_in, STDIN_FILENO);
		close(cmd->std_in);
	}
	if (cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->std_out, STDOUT_FILENO);
		close(cmd->std_out);
	}
	if (cmd->cmd)
	{
		if (execve(cmd->path, cmd->cmd, *envp) == -1)
			ft_parse_error(cmd);
	}
	exit(-1);
}

static int	update_envp(char ***envp, t_save_struct *tstruct)
{
	*envp = ft_envp_to_char(tstruct);
	return (0);
}

int	ft_execve_single_cmd(t_cmd *cmd, char ***envp, t_save_struct *tstruct)
{
	int	return_value;

	return_value = 0;
	if (is_it_builtin(cmd, &tstruct->envp, tstruct) == 1)
	{
		if (apply_redir(cmd) == -1)
			return (ft_return_code(ft_strdup("1"), &tstruct->envp));
		return_value = ft_dispatch_builtin(cmd, tstruct, 0);
		if (return_value != -1)
		{
			if (update_envp(envp, tstruct) == -1)
				return (exit_error("environnement expand failed\n", tstruct),
					0);
			return (return_value);
		}
	}
	cmd->pid = fork();
	ft_signal(0);
	if (cmd->pid == -1)
		exit_error("fork failed", tstruct);
	if (cmd->pid == 0)
		manage_single_child(cmd, envp);
	else
		wait_for_child(cmd, &return_value);
	return (return_value);
}
