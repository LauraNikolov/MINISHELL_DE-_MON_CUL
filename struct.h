#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum s_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	O_BRACKET,
	C_BRACKET,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	NO_TYPE,
}					t_token_type;

					


typedef struct s_cmd
{
	pid_t			pid;
	char			**cmd;
	char			*path;
	int				prev_fd;
	int				std_out;
	int				std_in;
	int				pipe[2];
	int				return_value;
	struct s_redir	*redir;
	int				*bool_bracket;
	char			*exp_code;
	t_token_type	type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_envp	*env;
}					t_cmd;

typedef struct t_ast
{
	t_cmd			*cmd;
	struct t_ast	*left;
	struct t_ast	*right;
	struct t_ast	*parent;
}					t_ast;

typedef struct s_redir
{
	char			*redir;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_envp
{
	char			*var_name;
	char			*var_value;
	int				print_flag;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

typedef struct s_exec
{
	int				std_in;
	int				std_out;
	int				prev;
	int				return_value;
	int				pipe[2];
}					t_exec;

typedef struct save_struct
{
	struct t_ast	*save_root;
	struct s_cmd	*cmd;
	int				redir_flag;
	struct t_ast	*ast;
	struct s_envp	*envp;
	struct s_exec	*exec;
	char			*save_spaces;
}					save_struct;

typedef struct s_data_parsing
{
	char *buffer;
	char *cmd;
	int bufflen;
	int cmd_index;
	int i;
	char *exp;
	int k;
	struct save_struct *t_struct;
} t_data_parsing;


#endif