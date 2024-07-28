#include "../minishell.h"

void	ft_print_env(t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->var_name, 1);
		if (curr->var_value)
		{
			write(1, "=\"", 3);
			ft_putstr_fd(curr->var_value, 1);
			write(1, "\"", 2);
		}
		else if (curr->print_flag && !curr->var_value)
			write(1, "=\"\"", 4);
		write(1, "\n", 2);
		curr = curr->next;
	}
}

void	ft_sort_env(t_envp **env)
{
	t_envp	*curr;

	if (!env || !*env)
		return ;
	curr = *env;
	while (curr->next)
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_content(&curr->var_name, &curr->next->var_name);
			ft_swap_content(&curr->var_value, &curr->next->var_value);
			curr = *env;
		}
		else
			curr = curr->next;
	}
}
static void	ft_add_var(int flag, char c, char *var, t_envp **env)
{
	if (!flag && c == '=')
		add_to_envp_lst(env, create_envp_node(var, 1));
	else if (!flag)
		add_to_envp_lst(env, create_envp_node(var, 0));
}

static void	ft_compare_var(t_envp **env, char *var)
{
	t_envp	*curr;
	int		i;
	int		flag;

	flag = 0;
	i = ft_strchr(var, '=');
	if (i == -1)
		i = ft_strlen(var);
	curr = *env;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, var, i))
		{
			if ((size_t)i != ft_strlen(curr->var_name))
				break ;
			flag = 1;
			if (var[i + 1])
				ft_override_content(&curr->var_value, &var[i + 1]);
			if (var[i] == '=')
				curr->print_flag = 1;
		}
		curr = curr->next;
	}
	ft_add_var(flag, var[i], var, env);
}

static int	ft_fork_export(t_envp **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_sort_env(env);
		ft_print_env(env);
		exit(0);
	}
	else
		wait(NULL);
	return (0);
}

static int	ft_handle_export_err(char *var)
{
	int	j;

	if (var[0] == '=')
	{
		ft_putstr_cmd_fd("Minishell : export: `", 2, NULL, 2);
		ft_putstr_cmd_fd(var, 2, NULL, 2);
		ft_putstr_cmd_fd("': not a valid identifier", 2, NULL, 0);
		return (1);
	}
	j = 0;
	while (var[j] && var[j] != '=')
	{
		if (var[j] == '-' || !ft_isalpha(var[0]))
		{
			ft_putstr_cmd_fd("Minishell : export: `", 2, NULL, 2);
			ft_putstr_cmd_fd(var, 2, NULL, 2);
			ft_putstr_cmd_fd("': not a valid identifier", 2, NULL, 0);
			return (1);
		}
		j++;
	}
	return (0);
}
int	ft_export(t_cmd *node, t_envp **env)
{
	int		i;
	char	**var;

	var = node->cmd;
	if (!env || !*var)
		return (0);
	if (!var[1])
		return (ft_fork_export(env));
	i = 1;
	while (var[i])
	{
		if (ft_handle_export_err(var[i]))
			return (ft_return_code(ft_strdup("1"), env));
		else
			ft_compare_var(env, var[i]);
		i++;
	}
	return (ft_return_code(ft_strdup("0"), env));
}
