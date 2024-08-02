/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:09:11 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 14:33:59 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:09:11 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 14:30:08 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_launch_exec(t_save_struct *tstruct)
{
	char	**envp;

	envp = ft_envp_to_char(tstruct);
	ft_exec(tstruct, &envp);
}

int	main(int ac, char **av, char **envp)
{
	char			*buffer;
	t_envp			*env;
	t_save_struct	*tstruct;

	(void)av;
	(void)ac;
	env = NULL;
	ft_save_envp(envp, &env);
	while (1)
	{
		ft_signal(1);
		tstruct = malloc(sizeof(t_save_struct));
		if (!tstruct)
			return (ft_free_envp_lst(env, NULL), 0);
		ft_memset(tstruct, 0, sizeof(*tstruct));
		buffer = readline("minishell : ");
		if (!buffer)
			return (ft_free_envp_lst(tstruct->envp, &env), free(buffer),
				ft_all_free(tstruct, 0, NULL, NULL), 0);
		add_history(buffer);
		if (ft_tokenize(buffer, tstruct, &env) != -1)
			ft_launch_exec(tstruct);
		ft_all_free(tstruct, 1, &buffer, &env);
	}
	return (0);
}
