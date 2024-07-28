# Compiler options
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
CC = gcc

# Directories
PARSEDIR = parse
EXECDIR = exec
LIBFTDIR = libft
BUILTINSDIR = builtins

# Source files
PARSE_SRCS = $(wildcard $(PARSEDIR)/*.c)
BUILTINS_SRCS = $(wildcard $(BUILTINSDIR)/*.c)
EXEC_SRCS = $(wildcard $(EXECDIR)/*.c)
MAIN_SRCS = main.c

# Object files
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
BUILTINS_OBJS = $(BUILTINS_SRCS:.c=.o)
EXEC_OBJS = $(EXEC_SRCS:.c=.o)
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# Static library
LIBFT = $(LIBFTDIR)/libft.a

# Executable name
NAME = minishell

# Targets
$(LIBFT):
	@echo "Compiling libft..."
	+@make -C $(LIBFTDIR)
	@echo "Libft compiled successfully"

$(NAME): $(LIBFT) $(PARSE_OBJS) $(BUILTINS_OBJS) $(EXEC_OBJS) $(MAIN_OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFTDIR) -lft $(LDFLAGS)
	@echo "Compilation successful: $@"

all: $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -f $(PARSE_OBJS) $(BUILTINS_OBJS) $(EXEC_OBJS) $(MAIN_OBJS)
	+@make -C $(LIBFTDIR) clean

fclean: clean
	@echo "Removing binary: $(NAME)..."
	@rm -f $(NAME)
	+@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
