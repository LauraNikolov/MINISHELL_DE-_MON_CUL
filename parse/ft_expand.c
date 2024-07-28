#include "../minishell.h"

/* if (s[i] == '$' && s[i + 1] == '{')
		{
			while (s[i + var_len] && !ft_is_str(s[i + var_len], "\'\" $")
					&& !ft_is_str(s[i + var_len - 1], "}"))
				var_len++;
			if (ft_bad_subst(&s[i + 2]))
				ft_putstr_cmd_fd("minishell: bad_substition ", 2, &s, 0);
			var = ft_strndup(&s[i + 2], var_len - 3);
			var_value = ft_search_var(var, env);
			var_value_len += ft_strlen(var_value);
			if (var_value && exp_flag && (*exp_code)[l++] == '1')
			{
				k = 0;
				while (var_value[k])
					(*exp)[j++] = var_value[k++];
			}
			i += var_len - 1;
			free(var);
			var_value = NULL;
		} */

int	ft_bad_subst(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	if (s[i] != '}' || i == 0)
		return (1);
	return (0);
}

static int	ft_expand_math(char *s, t_envp **env, int len)
{
	char	*var_value;
	char	*var;
	int		var_len;
	int		var_value_len;

	var = ft_strndup(s, len);
	var_value = ft_search_var(var, env);
	var_value_len = ft_strlen(var_value);
	var_len = ft_strlen(var) + 1;
	ft_safe_free(&var);
	return (var_len - var_value_len);
}

static int	ft_expand_len(char *s, t_envp **env, char **exp_code)
{
	int	i;
	int	j;
	int	len;
	int	total_var_len;

	total_var_len = 0;
	j = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1])) && s[i + 1] != '?')
		{
			if (*exp_code && (*exp_code)[j] == '1')
			{
				len = 1;
				while (s[i + len] && !ft_is_str(s[i + len], "\'\" $}"))
					len++;
				total_var_len += ft_expand_math(&s[i + 1], env, len - 1);
				i += len - 1;
			}
			j++;
		}
	}
	return (i - total_var_len);
}

static int	ft_cpy_expand_2(char *s, char **exp, int *j, t_envp **env)
{
	char	*var_value;
	char	*var;
	int		i;
	int		index;
	int		len;

	index = 0;
	i = 0;
	len = 1;
	while (s[i + len] && !ft_is_str(s[i + len], "\'\" $}"))
		len++;
	var = ft_strndup(&s[i + 1], len - 1);
	var_value = ft_search_var(var, env);
	index = 0;
	if (var_value)
		while (var_value[index])
			(*exp)[(*j)++] = var_value[index++];
	i += len;
	ft_safe_free(&var);
	return (i);
}

void	ft_cpy_expand(char *s, t_data_parsing *data, t_envp **env,
		char **exp_code)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && ft_isalnum(s[i + 1]) && s[i + 1] != '?')
		{
			if (*exp_code && (*exp_code)[data->k] == '1')
				i += ft_cpy_expand_2(&s[i], &data->exp, &j, env);
			else if (*exp_code && (*exp_code)[data->k] == '0')
			{
				(data->exp)[j++] = s[i++];
			}
			data->k++;
		}
		else
			(data->exp)[j++] = s[i++];
	}
	(data->exp)[j] = '\0';
}

static int	ft_count_return_code(char *s, t_envp **env)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "$?", 2))
		{
			count += ft_strlen(ft_search_var("?", env));
			count -= 2;
		}
		i++;
	}
	return (count + ft_strlen(s));
}

static int	ft_match_return_val(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "$?", 2))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_concat_return_var(char *s, t_envp **env, char **res)
{
	char	*var_value;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "$?", 2))
		{
			var_value = ft_search_var("?", env);
			k = 0;
			while (var_value[k])
				(*res)[j++] = var_value[k++];
			i += 2;
		}
		(*res)[j++] = s[i++];
	}
	(*res)[j] = '\0';
}

static char	*ft_expand_return_var(char *s, t_envp **env, char **exp_code,
		int *l)
{
	char	*res;

	res = NULL;
	if (ft_match_return_val(s))
	{
		if (*exp_code && (*exp_code)[*l] == '1')
		{
			res = malloc(sizeof(char) * (ft_count_return_code(s, env + 1)));
			if (!res)
				return (NULL);
			ft_concat_return_var(s, env, &res);
			(*l)++;
			return (ft_strdup(res));
		}
	}
	return (ft_strdup(s));
}

void	ft_expand(t_cmd *node, t_envp **env, save_struct *t_struct)
{
	int				i;
	int				len;
	t_data_parsing	data;

	i = -1;
	ft_memset(&data, '0', sizeof(t_data_parsing));
	data.exp = NULL;
	data.k = 0;
	while (node->cmd[++i])
	{
		if (ft_is_char(node->cmd[i], '$'))
		{
			data.exp = ft_strdup(node->cmd[i]);
			ft_safe_free(&node->cmd[i]);
			node->cmd[i] = ft_expand_return_var(data.exp, env, &node->exp_code,
					&data.k);
			ft_safe_free(&data.exp);
			len = ft_expand_len(node->cmd[i], env, &node->exp_code) + 1;
			ft_safe_malloc(&data.exp, len, t_struct);
			ft_cpy_expand(node->cmd[i], &data, env, &node->exp_code);
			ft_safe_free(&node->cmd[i]);
			node->cmd[i] = ft_strdup(data.exp);
			ft_safe_free(&data.exp);
		}
	}
}
