# Compiler options
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
CC = cc

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Directories
PARSEDIR = parse
EXECDIR = exec
LIBFTDIR = libft
BUILTINSDIR = builtins

# Parsing files
PARSE_SRCS = parse/clean_lst.c \
parse/ft_create_token_lst.c \
parse/ft_expand.c \
parse/ft_expand_2.c \
parse/ft_is_enum.c \
parse/ft_envp_to_char.c \
parse/ft_get_path.c \
parse/ft_get_symb.c \
parse/ft_handle_quote.c \
parse/ft_parse_redir.c \
parse/ft_return_code.c \
parse/ft_save_envp.c \
parse/ft_tokenize.c \
parse/ft_wildcard.c \
parse/ft_wildcard_2.c \
parse/lst_utils.c \
parse/lst_utils_2.c \
parse/lst_utils_3.c \
parse/syntax_functions.c \
parse/syntax_functions2.c \
parse/syntax_functions3.c \
parse/utils.c \
parse/utils2.c \
parse/utils_3.c \

# Builtins files
BUILTINS_SRCS = builtins/echo.c \
builtins/env.c \
builtins/exit.c \
builtins/ft_pwd.c \
builtins/export.c \
builtins/export_2.c \
builtins/unset.c \
builtins/ft_cd.c \
builtins/ft_dispatch_builtin.c \
builtins/echo_2.c \

# Execution files
EXEC_SRCS = exec/ast_utils.c \
exec/ast_utils2.c \
exec/error.c \
exec/exec_ast.c \
exec/exec_ast2.c \
exec/exec_ast3.c \
exec/exec_parse.c \
exec/exec_pipe.c \
exec/exec_single_cmd.c \
exec/exec_utils.c \
exec/fork.c \
exec/heredoc.c \
exec/heredoc2.c \
exec/leaf.c \
exec/redir.c \
exec/redir2.c \

# Main file
MAIN_SRCS = main.c \

# Object files
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
BUILTINS_OBJS = $(BUILTINS_SRCS:.c=.o)
EXEC_OBJS = $(EXEC_SRCS:.c=.o)
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

OBJS= $(PARSE_OBJS) $(BUILTINS_OBJS) $(EXEC_OBJS) $(MAIN_OBJS)

# Static library
LIBFT = $(LIBFTDIR)/libft.a

# Executable name
NAME = minishell

# Targets
all: $(NAME)

bonus: fclean all

$(LIBFT):
	@echo -e "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFTDIR)
	@echo -e "$(GREEN)Libft compiled successfully$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo -e "$(YELLOW)"
	@echo	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"  
	@echo	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║"   
	@echo 	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║" 
	@echo	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"     
	@echo	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"                                                             
	@echo -e "$(RESET)"
	@echo -e "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo -e "$(GREEN)Compilation successful: $@$(RESET)"

# Pattern rule for object files
%.o: %.c
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo -e "$(RED)Removing binary: $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re ascii_art