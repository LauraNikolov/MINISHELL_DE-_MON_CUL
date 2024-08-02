/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:06:17 by lnicolof          #+#    #+#             */
/*   Updated: 2024/08/02 13:55:21 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_limiter(char *s1, char *s2)
{
	int	i;
	int	len;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		if (!ft_strncmp(s1, &s2[i], len))
		{
			if (len == (int)ft_strlen(s2) - 1)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	heredoc_parent(pid_t pid, int file)
{
	(void)pid;
	ft_signal(3);
	waitpid(pid, &g_exit_status, 0);
	close(file);
	write(1, "\n", 1);
}
