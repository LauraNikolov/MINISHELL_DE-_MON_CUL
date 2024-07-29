/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:39:53 by lnicolof          #+#    #+#             */
/*   Updated: 2024/07/29 15:36:45 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_limiter(char *s1, char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s2[i])
	{
		y = 0;
		while (s2[i] == s1[y] && s1[y] && s2[i])
		{
			i++;
			y++;
			if (y == (int)ft_strlen(s1))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*create_here_doc(char *str, char *limiter)
{
	int		file;
	char	*line;
	int pid;

	pid = fork();
	if(pid == 0)
	{
		ft_signal(2);
	file = open(str, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (file == -1)
		perror("open:");
	while (1)
	{
		write(1, "here_doc>  ", 10);
		line = get_next_line(STDOUT_FILENO);
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}
		if (ft_limiter(limiter, line) == 1)
			break ;
		write(file, line, ft_strlen(line) - 1);
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close(file);
	exit(0);
	}
	else
	{

		ft_signal(3);
		wait(0);
		write(1, "\n", 1);
		ft_signal(1);
	}
	return (str);
}

static void	handle_heredoc(t_redir *redir, int i, t_save_struct *tstruct)
{
	char	*heredocname;

	heredocname = ft_strjoin(ft_itoa(i), "heredoctmp");
	if (redir->type == R_HEREDOC)
	{
		redir->next->redir = create_here_doc(heredocname, redir->next->redir);
		if (!redir->next->redir)
			exit_error("heredoc failed\n", tstruct);
	}
}

static void	process_redirections(t_cmd *cmd, int *i, t_save_struct *tstruct)
{
	t_redir	*current_redir;

	current_redir = cmd->redir;
	while (current_redir && current_redir->type == R_HEREDOC)
	{
		handle_heredoc(current_redir, *i, tstruct);
		if (current_redir->next)
			current_redir = current_redir->next->next;
		else
			current_redir = NULL;
		(*i)++;
	}
}

void	manage_heredoc(t_cmd *cmd, t_save_struct *tstruct)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = cmd;
	while (current)
	{
		if (current->redir)
			process_redirections(current, &i, tstruct);
		current = current->next;
	}
}
