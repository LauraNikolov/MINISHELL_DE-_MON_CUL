/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:53:09 by melmarti          #+#    #+#             */
/*   Updated: 2024/08/01 19:06:58 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lst_env_size(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static int	ft_var_size(t_envp *node)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (!node)
		return (0);
	if (node->var_name)
	{
		while (node->var_name[i])
		{
			i++;
			len++;
		}
	}
	i = 0;
	if (node->var_value)
	{
		while (node->var_value[i])
		{
			i++;
			len++;
		}
	}
	return (len + 1);
}

static char	**ft_split_envp(char ***env1, t_envp *env)
{
	int		j;
	int		l;
	int		k;
	char	**envp;

	envp = *env1;
	j = 0;
	while (env)
	{
		envp[j] = malloc(sizeof(char) * (ft_var_size(env) + 1));
		if (!*envp)
			return (NULL);
		k = 0;
		l = 0;
		while (env->var_name[l])
			envp[j][k++] = env->var_name[l++];
		envp[j][k++] = '=';
		l = 0;
		if (env->var_value)
			while (env->var_value[l])
				envp[j][k++] = env->var_value[l++];
		envp[j][k] = '\0';
		env = env->next;
		j++;
	}
	envp[j] = NULL;
	return (envp);
}

char	**ft_envp_to_char(t_save_struct *tstruct)
{
	char	**env_char;
	int		i;

	if (tstruct->envp_to_char)
	{
		i = 0;
		while (tstruct->envp_to_char[i])
		{
			ft_safe_free(&tstruct->envp_to_char[i]);
			i++;
		}
		free(tstruct->envp_to_char);
	}
	env_char = malloc(sizeof(char *) * (ft_lst_env_size(tstruct->envp) + 1));
	if (!env_char)
		return (NULL);
	env_char = ft_split_envp(&env_char, tstruct->envp);
	tstruct->envp_to_char = env_char;
	return (env_char);
}
