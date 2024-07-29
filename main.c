/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:09:11 by melmarti          #+#    #+#             */
/*   Updated: 2024/07/29 13:03:15 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	t_envp		*env;
	t_save_struct	*t_struct;

	(void)av;
	(void)ac;
	env = NULL;
	ft_save_envp(envp, &env);
	while (1)
	{
		ft_signal(1);
		t_struct = malloc(sizeof(t_save_struct));
		if (!t_struct)
			return (ft_free_envp_lst(&env, NULL), 0);
		ft_memset(t_struct, 0, sizeof(*t_struct));
		buffer = readline("minishell : ");
		if (!buffer)
			return (ft_free_envp_lst(&t_struct->envp, &env), free(buffer),
				ft_all_free(t_struct, 0, &buffer), 0);
		add_history(buffer);
		if (ft_tokenize(buffer, t_struct, &env) != -1)
			ft_exec(t_struct, ft_envp_to_char(t_struct->envp));
		ft_all_free(t_struct, 1, &buffer);
	}
	return (0);
}
