#include "../minishell.h"

int	ft_check_pipe(t_cmd *node, t_envp **env, save_struct *t_struct)
{
	(void)t_struct;
	if (!node->prev || !node->next)
	{
		ft_putstr_cmd_fd("minishell: syntax error near unexpected token `", 2,
			&node->next->cmd[0], 0);
		return (ft_return_code(ft_strdup("2"), env));
	}
	if (!(node->prev->type == WORD || node->prev->type == C_BRACKET)
		&& (node->next->type == R_OUT || node->next->type == R_IN
			|| node->next->type == R_APPEND || node->next->type == R_HEREDOC
			|| node->next->type == WORD))
	{
		ft_putstr_cmd_fd("minishell: syntax error near unexpected token `", 2,
			&node->next->cmd[0], 0);
		return (ft_return_code(ft_strdup("2"), env));
	}
	return (0);
}

int	ft_bad_expression(t_cmd *node)
{
	if (!node->next)
		return (0);
	if (node->next->type == WORD)
	{
		if (node->next->cmd[1])
		{
			ft_putstr_cmd_fd("minishell: syntax error in expression :", 2,
				node->next->cmd, 1);
			return (1);
		}
	}
	return (0);
}