/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:43:25 by renard            #+#    #+#             */
/*   Updated: 2024/08/02 17:55:37 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_fd(int flag, t_cmd *cmd, int *fd)
{
	*fd = cmd->std_out;
	if (!flag)
	{
		if (!cmd->redir)
			*fd = 1;
		else if (cmd->std_out != STDOUT_FILENO)
			*fd = cmd->std_out;
		else
			*fd = 1;
	}
	if (flag)
	{
		if (!cmd->redir)
			*fd = STDOUT_FILENO;
		else
			*fd = redir_out(cmd);
	}
}

int	ft_echo_return(int flag, int *fd, t_envp **env)
{
	ft_putchar_fd('\n', *fd);
	if (*fd != STDOUT_FILENO && flag)
		close(*fd);
	return (ft_return_code(ft_strdup("127"), env));
}
