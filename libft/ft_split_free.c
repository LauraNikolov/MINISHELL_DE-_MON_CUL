/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:03:31 by melmarti          #+#    #+#             */
/*   Updated: 2024/07/29 14:22:06 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **strs, int n)
{
	int	i;

	i = 0;
	if (!strs[n])
	{
		while (strs[i])
			free(strs[i++]);
		free(strs);
	}
	return ;
}
