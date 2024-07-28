#include "../minishell.h"

static void	ft_encode_spaces(char **cmd, t_data_parsing *data, char c,
		int *new_cmd_index)
{
	if (*cmd)
		(*cmd)[*new_cmd_index] = c;
	if (!data->t_struct)
		return ;
	printf("cmd_index = %d, cmd = %s\n et data bufflen === %d", *new_cmd_index, *cmd, data->bufflen);
	if ((*cmd)[*new_cmd_index] != ' ')
	{
		if (data->bufflen == -1)
			ft_strcat(data->t_struct->save_spaces, "6");
		else
			ft_strcat(data->t_struct->save_spaces, "3");
	}
	else
		ft_strcat(data->t_struct->save_spaces, "2");
}

int	ft_quote_len(char *s, int len)
{
	int		i;
	int		var_size;
	int		quote_flag;
	int		quote_len;
	char	c;

	quote_flag = -1;
	var_size = 0;
	i = -1;
	quote_len = 0;
	c = '\0';
	while (s[++i] && i < len)
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			quote_len++;
		}
	}
	if (quote_len % 2 != 0)
		return (-1);
	return (i + var_size - quote_len);
}

/* void	ft_while_quote(int len, t_data_parsing *data, t_redir *redir, char *s)
{
	printf("c = %c\n",s[data->i] );
	if (s[data->i] == '\'' || s[data->i] == '\"')
		data->i += ft_inside_quote(&s[data->i + 1], data);
	else if (ft_is_str(s[data->i], "><"))
	{
		add_to_redir_lst(&redir, ft_redir(s, &data->i, len, data));
		data->i -= 2;
	}
	else
	{
		ft_encode_spaces(data, &data->cmd_index, s[data->i]);
		data->cmd_index++;
	}
}

t_redir	*ft_handle_quote(char *s, int len, t_data_parsing *data, char **cmd)
{
	t_redir	*redir;
	t_redir	*redir;
	t_redir	*redir;
	int		new_cmd_index;

	redir = NULL;
	if (data->t_struct && !data->t_struct->save_spaces)
		if (ft_safe_malloc(&(data->t_struct->save_spaces), data->bufflen + 1,
				data->t_struct) == -1)
			return (NULL);
	if (ft_safe_malloc(cmd, (ft_quote_len(s, len) + 1), data->t_struct) == -1)
		return (NULL);
	data->i = 0;
	data->cmd_index = 0;
	while (s[data->i] && data->i < len)
	{
		printf("s == %s", &s[data->i]);
		ft_while_quote(len, data, redir, s);
		data->i++;
	}
	return (redir);
} */
t_redir	*ft_handle_quote(char *s, int len, t_data_parsing *data, char **cmd)
{
	t_redir	*redir;

	int		new_cmd_index;
	new_cmd_index = 0;
	redir = NULL;
	if (ft_safe_malloc(cmd, (ft_quote_len(s, len) + 1), data->t_struct) == -1)
		return (NULL);
	data->i = 0;
	data->cmd_index = 0;
	while (s[data->i] && data->i < len)
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			data->i += ft_inside_quote(&s[data->i + 1], data, cmd,
					&new_cmd_index);
		else if (ft_is_str(s[data->i], "><"))
		{
			add_to_redir_lst(&redir, ft_redir(s, len, data));
			data->i -= 2;
		}
		else
		{
			ft_encode_spaces(cmd, data, s[data->i], &new_cmd_index);
			new_cmd_index++;
		}
		data->i++;
	}
	return (redir);
}

/* void	ft_else_inside_quote(t_data_parsing *data, char *s, int *i)
{
	int		i;
	char	c;

} */
int	ft_inside_quote(char *s, t_data_parsing *data, char **cmd,
		int *new_cmd_index)
{
	int		i;
	char	c;

	i = 0;
	c = s[-1];
	while (s[i] && s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*new_cmd_index] = '/';
			if (data->bufflen == -1)
				ft_strcat(data->t_struct->save_spaces, "4");
			else
				ft_strcat(data->t_struct->save_spaces, "1");
			(*new_cmd_index)++;
		}
		else
		{
			(*cmd)[*new_cmd_index] = s[i];
			if (data->bufflen == -1)
				ft_strcat(data->t_struct->save_spaces, "5");
			else
				ft_strcat(data->t_struct->save_spaces, "0");
			(*new_cmd_index)++;
			// ft_else_inside_quote(data, s, &i);
		}
		i++;
	}
	return (i + 1);
}
