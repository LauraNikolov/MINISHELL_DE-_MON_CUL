/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:40 by lnicolof          #+#    #+#             */
/*   Updated: 2024/08/02 11:07:20 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*create_ast_node(t_cmd *cmd, t_ast *parent, t_save_struct *tstruct)
{
	t_ast	*node;

	while (cmd->type == C_BRACKET || cmd->type == O_BRACKET)
	{
		cmd = cmd->next;
	}
	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		exit_error("malloc failed\n", tstruct);
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return (node);
}

void	join_tree(t_ast *left, t_ast *right, t_ast *root)
{
	root->left = left;
	root->right = right;
}

static t_cmd	*find_logical_root(t_cmd *start, t_cmd *end)
{
	t_cmd	*current;
	t_cmd	*root;

	current = end;
	root = NULL;
	while (current != start)
	{
		if (current->type == AND || current->type == OR)
		{
			if (!root || count_parenthesis(current) < count_parenthesis(root))
				root = current;
		}
		current = current->prev;
	}
	return (root);
}

static t_cmd	*find_pipe_root(t_cmd *start, t_cmd *end)
{
	t_cmd	*current;

	current = end;
	while (current != start)
	{
		if (current->type == PIPE)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_ast	*build_ast_recursive(t_cmd *start, t_cmd *end, t_ast *parent,
		t_save_struct *tstruct)
{
	t_cmd	*root;
	t_cmd	*right_start;
	t_ast	*root_node;
	t_ast	*gauche;
	t_ast	*droit;

	root = find_logical_root(start, end);
	if (!root)
		root = find_pipe_root(start, end);
	if (!root)
		return (create_ast_node(start, parent, tstruct));
	right_start = root->next;
	root_node = create_ast_node(root, parent, tstruct);
	gauche = build_ast_recursive(start, root->prev, root_node, tstruct);
	droit = build_ast_recursive(right_start, end, root_node, tstruct);
	join_tree(gauche, droit, root_node);
	return (root_node);
}
