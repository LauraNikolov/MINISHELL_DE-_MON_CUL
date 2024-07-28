#include "../minishell.h"

int	ft_check_redir2(t_cmd *node, t_envp **env)
{
	t_redir	*tmp;

	tmp = node->redir;
	while (tmp->next)
	{
		if ((tmp->type >= 6 && tmp->type <= 9) && (!tmp->next
				|| (tmp->next->type >= 6 && tmp->next->type <= 9)
				|| tmp->next->type != WORD || !tmp->next->redir[0]))
		{
			if (!(tmp->next->type >= 6 && tmp->next->type <= 9))
				ft_putstr_cmd_fd("minishell: syntax error near unexpected token `newline'",
					1, NULL, 0);
			else
				ft_putstr_cmd_fd("minishell: syntax error near unexpected token `",
					2, &tmp->next->redir, 0);
			return (ft_return_code(ft_strdup("2"), env), -1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_redir(t_cmd *node, t_envp **env)
{
	t_redir	*tmp;

	if (!node->redir || !node->redir->next)
		return (0);
	tmp = node->redir;
	if (!ft_strcmp(tmp->next->redir, "*"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->next->redir, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (ft_return_code(ft_strdup("1"), env), -1);
	}
	if (!tmp->next || !tmp->next->redir[0])
	{
		ft_putstr_cmd_fd("minishell: syntax error near unexpected token `newline'",
			1, NULL, 0);
		return (ft_return_code(ft_strdup("2"), env), -1);
	}
	ft_check_redir2(node, env);
	return (0);
}

int	ft_check_word2(t_cmd *node, t_envp **env)
{
	if (node->next->type == O_BRACKET && !node->cmd[1])
	{
		ft_putstr_cmd_fd("minishell: syntax error near unexpected token `", 2,
			&node->next->next->cmd[0], 0);
		return (ft_return_code(ft_strdup("2"), env));
	}
	else if (node->next->type == O_BRACKET && node->cmd[1])
	{
		ft_putstr_cmd_fd("minishell: syntax error near unexpected token `", 2,
			&node->next->next->cmd[0], 0);
		return (ft_return_code(ft_strdup("2"), env));
	}
	
	return (0);
}

int	ft_check_word(t_cmd *node, t_envp **env, save_struct *t_struct)
{
	if (!node->cmd)
		return (0);
	
	if (!node->next)
	{
		ft_get_path(node, t_struct);
		if (ft_check_redir(node, env) != 0)
			return (-1);
		return (0);
	}
	if (node->next->next)
		if (ft_check_word2(node, env) != 0)
			return (-1);
	ft_get_path(node, t_struct);
	if (ft_check_redir(node, env) != 0)
		return (-1);
	return (0);
}

int	ft_check_Cbracket(t_cmd *node, t_envp **env, save_struct *t_struct)
{
	t_cmd	*curr;

	(void)t_struct;
	if (!node->next)
		return (0);
	if (node->next == WORD)
		return (-1);
	curr = node;
	while (curr)
	{
		if (curr->prev == NULL)
		{
			ft_putstr_cmd_fd("minishell: syntax error near unexpected token `",
				2, &node->next->cmd[0], 0);
			return (ft_return_code(ft_strdup("2"), env));
		}
		if (curr->prev->type == O_BRACKET)
			break ;
		curr = curr->prev;
	}
	return (0);
}

int	ft_is_enum(t_cmd *node, char **error_node)
{
	if (!node)
		return (0);
	if (node->type == PIPE || node->type == R_HEREDOC || node->type == R_APPEND
		|| node->type == C_BRACKET)
		return (0);
	else if (node->prev)
		*error_node = node->cmd[0];
	return (1);
}

int	ft_is_enum2(t_cmd *node, char **error_node)
{
	if (!node)
		return (1);
	if (node->type == R_OUT)
		return (1);
	else if (node->type == AND)
		return (1);
	else if (node->type == OR)
		return (1);
	else if (node->type == C_BRACKET)
		return (1);
	else if (node->type == PIPE)
		return (1);
	else if (!*error_node)
		*error_node = node->cmd[0];
	return (0);
}