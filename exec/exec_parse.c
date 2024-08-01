/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/08/01 18:23:47 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

static void	error_exec_str(char *str, char *cmd, int exit_code)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

void	ft_parse_error(t_cmd *cmd)
{
	struct stat	buf;

	if (stat(cmd->cmd[0], &buf) != -1)
	{
		if (((S_ISDIR(buf.st_mode)) && (!ft_strncmp("./", cmd->cmd[0], 2)))
			|| (cmd->cmd[0][ft_strlen(cmd->cmd[0]) - 1] == '/'))
			error_exec_str("Is a directory", cmd->cmd[0], 126);
		if (!(buf.st_mode & S_IXUSR) || !(buf.st_mode & S_IRUSR)
			|| !S_ISLNK(buf.st_mode) || !S_ISDIR(buf.st_mode))
			error_exec_str("Permission denied\n", cmd->cmd[0], 126);
	}
	if (ft_strncmp("./", cmd->cmd[0], 2) == 0 || ft_strncmp("/", cmd->cmd[0],
			1) == 0)
		error_exec_str("No such file or directory\n", cmd->cmd[0], 127);
	else
		error_exec_str("command not found\n", cmd->cmd[0], 127);
}

void	close_fds(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (current->std_out != 1)
		{
			close(current->std_out);
			current->std_out = 1;
		}
		if (current->std_in != 0)
		{
			close(current->std_in);
			current->std_in = 0;
		}
		if (current->type == R_HEREDOC)
			free(current->next->redir);
		current = current->next;
	}
}

void	destroy_tmp_file(t_cmd *cmd)
{
	t_cmd	*current;
	t_redir	*current_redir;

	current = cmd;
	while (current)
	{
		if (current->redir)
		{
			current_redir = current->redir;
			while (current_redir)
			{
				if (current_redir->type == R_HEREDOC)
					unlink(current_redir->next->redir);
				current_redir = current_redir->next->next;
			}
		}
		current = current->next;
	}
}

void	ft_exec(t_save_struct *tstruct, char ***envp)
{
	int	cmd_size;
	int	return_value;

	return_value = 0;
	cmd_size = ft_nbr_of_cmd(tstruct->cmd);
	if (cmd_size == 1)
	{
		tstruct->cmd->std_in = 0;
		tstruct->cmd->std_out = 1;
		manage_heredoc(tstruct->cmd, tstruct);
		if(g_exit_status != 5)
			return_value = ft_execve_single_cmd(tstruct->cmd, envp, tstruct);
		close_fds(tstruct->cmd);
		ft_return_code(ft_itoa(return_value), &tstruct->envp);
		destroy_tmp_file(tstruct->cmd);
	}
	else
	{
		manage_heredoc(tstruct->cmd, tstruct);
		if(g_exit_status != 5)
			ft_exec_multi_cmds(tstruct, envp);
		close_fds(tstruct->cmd);
		destroy_tmp_file(tstruct->cmd);
		recursive_free_ast(&tstruct->ast);
	}
}
