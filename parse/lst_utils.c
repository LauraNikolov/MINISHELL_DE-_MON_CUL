/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:37 by renard            #+#    #+#             */
/*   Updated: 2024/07/29 00:36:43 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_envp(t_envp **envp)
{
	t_envp	*curr;

	curr = *envp;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
		printf("%s", curr->var_name);
		printf("=%s\n", curr->var_value);
		curr = curr->next;
	}
	return (0);
}

void	ft_print_lst(t_cmd *node)
{
	t_cmd	*curr;
	t_redir	*curr_redir;
	int		i;
	int		command_num;

	i = 1;
	command_num = 1;
	curr = node;
	while (curr)
	{
		if (curr->cmd)
		{
			printf("\nCommande n%d = %s\n", command_num, curr->cmd[0]);
			while (curr->cmd[i])
			{
				printf("Options n%d : %s\n", i, curr->cmd[i]);
				i++;
			}
		}
		if (curr->redir)
		{
			// printf("Path = %s\n", curr->path);
			curr_redir = curr->redir;
			while (curr_redir)
			{
				printf("redir = %s | type = ", curr_redir->redir);
				if (curr_redir->type == 6)
					printf(" R_IN\n");
				else if (curr_redir->type == 0)
					printf("INFILE\n");
				else if (curr_redir->type == 7)
					printf(" R_OUT\n");
				else if (curr_redir->type == 8)
					printf("R_APPEND\n");
				else if (curr_redir->type == 9)
					printf("HEREDOC\n");
				curr_redir = curr_redir->next;
			}
		}
		if (curr->type == 0)
			printf("WORD\n");
		else if (curr->type == 1)
			printf("PIPE\n");
		else if (curr->type == 2)
			printf("AND\n");
		else if (curr->type == 3)
			printf("OR\n");
		else if (curr->type == 8)
			printf("O_BRACKET\n");
		else if (curr->type == 9)
			printf("C_BRACKET\n");
		printf("\n----\n");
		command_num++;
		curr = curr->next;
		i = 1;
	}
}
t_cmd	*lst_last(t_cmd *node)
{
	t_cmd	*curr;
	
	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_redir	*lst_last_redir(t_redir *node)
{
	t_redir	*curr;

	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_envp	*lst_envp_last(t_envp *node)
{
	t_envp	*curr;

	if (!node)
		return (NULL);
	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}
