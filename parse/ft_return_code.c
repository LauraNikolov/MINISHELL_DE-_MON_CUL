/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:30:19 by renard            #+#    #+#             */
/*   Updated: 2024/08/02 17:44:41 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_return_code(char *code, t_envp **env)
{
	t_envp	*curr;

	if (!env)
		return (0);
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			ft_safe_free(&curr->var_value);
			curr->var_value = ft_strdup(code);
			break ;
		}
		curr = curr->next;
	}
	free(code);
	return (ft_atoi(curr->var_value));
}
