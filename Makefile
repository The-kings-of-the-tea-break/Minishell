NAME		=	minishell

CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP

SRCS_DIR	=	srcs
OBJ_DIR		=	objs
SRCS_NAMES	=	main.c write_str.c \
				clean/free_data.c \
				clean/exit_status.c \
				signal/signal.c \
				signal/signal_heredoc.c \
				signal/signal_child.c \
				builtins/get_env.c \
				builtins/env.c \
				builtins/unset.c \
				builtins/get_export_env.c \
				builtins/syntaxe_export.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/cd.c \
				builtins/cd_utils.c \
				builtins/pwd.c \
				builtins/exit.c \
				builtins/echo.c \
				token/add_token.c \
				token/check_token_type2.c \
				token/check_token_type.c \
				token/get_path.c \
				token/token_copy.c \
				token/token_copy_word.c \
				token/tokenize.c \
				token/token_utils.c \
				parse/syntaxe.c \
				parse/parse.c \
				parse/syntaxe_line.c \
				parse/remove_quote.c \
				exec/env_to_send.c \
				exec/exec_dup2.c \
				exec/open_file.c \
				exec/exec_utils.c \
				exec/exec_pipes.c \
				exec/heredoc.c \
				exec/simple_exec.c \
				exec/exec.c \
				expand/expand.c \
				expand/expand_utils.c \
				expand/expand_utils2.c \
				expand/expand_dollars.c \
				
OBJS_NAMES	=	$(SRCS_NAMES:.c=.o)
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS		=	$(addprefix $(OBJ_DIR)/,$(OBJS_NAMES))

HEADER		=	-Iincludes/

LIBFT		=	libft/libft.a

GREEN		=	\033[1;32m
RED			=	\033[1;31m
YELLOW		=	\033[1;33m
ORANGE		=	\033[38;5;214m
PURPLE		=	\033[1;35m
BOLD		:=	\033[1m
RESET		=	\033[0m

SUCCESS		=	[ ✔ ]
ERROR		=	[ ✗ ]
CLEAN		=	[ ♻ ]
REMOVE		=	[ 🗑 ]
REDO		=	[ 🗘 ]

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) $(HEADER) $(LIBFT) -lreadline -o $(NAME) || (echo "\n$(RED) ============ $(ERROR) Linking failed ! ====================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Executable created ! ================================== $(RESET)"

$(LIBFT):
	@make -C libft --no-print-directory

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADER) || (echo "\n$(RED) ============ $(ERROR) Compilation failed ! ================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Successful compilation ! ============================== $(RESET)"

clean:
	@make clean -C libft --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW) ============ $(CLEAN) Successful binary & dependances cleaning ! ============ $(RESET)"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -rf $(NAME)
	@echo "$(BOLD)$(ORANGE) ============ $(REMOVE) Deleted executable ! ================================== $(RESET)"

re: fclean all
	@echo "$(PURPLE) ============ $(REDO) Redo completed ! ====================================== $(RESET)"

.PHONY: all clean fclean re

-include $(DEPS)