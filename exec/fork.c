/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/08/01 18:24:24 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_multi_cmds(t_save_struct *tstruct, char ***envp)
{
	t_cmd	*start;
	t_cmd	*end;
	int		return_value;

	return_value = -1;
	start = tstruct->cmd;
	while (tstruct->cmd->next)
		tstruct->cmd = tstruct->cmd->next;
	end = tstruct->cmd;
	tstruct->cmd = start;
	tstruct->ast = build_ast_recursive(start, end, NULL, tstruct);
	start = tstruct->cmd;
	while (start)
	{
		start->std_in = STDIN_FILENO;
		start->std_out = STDOUT_FILENO;
		start->prev_fd = -1;
		start->return_value = 0;
		start = start->next;
	}
	tstruct->save_root = tstruct->ast;
	return_value = exec_ast_recursive(tstruct->ast, envp, return_value,
			tstruct);
	if (ft_return_code(ft_itoa(return_value), &tstruct->envp) == -1)
		exit_error("malloc failed\n", tstruct);
}
