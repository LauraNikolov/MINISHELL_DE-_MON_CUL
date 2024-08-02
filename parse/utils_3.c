/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:35 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/02 17:46:15 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_is_alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' || s[i] <= 'z') || (s[i] >= 'A' || s[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}