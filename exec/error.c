/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:37:50 by lnicolof          #+#    #+#             */
/*   Updated: 2024/07/29 13:22:47 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(char *str, t_save_struct *tstruct)
{
	ft_putstr_fd(str, 2);
	ft_free_envp_lst(&tstruct->envp, NULL);
	ft_all_free(tstruct, 0, NULL);
	exit(134);
}
