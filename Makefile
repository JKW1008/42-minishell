CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS_DEBUG = -fsanitize=address -g
MAKE = make --no-print-directory
NAME = minishell
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

HEADR = ./includes/minishell.h \
		./includes/parse.h

SRCS_DIR = ./srcs
OBJS_DIR = ./objs

SRCS =	ms_main.c \
		ms_init.c \
		ms_signal.c \
		ms_prompt.c \
		ms_execute.c \
		ms_parse/ms_lexer.c \
		ms_parse/ms_lex_util.c \
		ms_parse/ms_tokenize.c \
		ms_parse/ms_parse.c \
		ms_parse/ms_alloc_simplecmd.c \
		ms_parse/ms_alloc_rdr.c \
		ms_parse/ms_tokens_type_utils.c \
		utils/ms_char_handle.c \
		utils/ms_err_handle.c \
		utils/ms_find_path.c \
		utils/ms_excute_utils.c \
		utils/ms_free_utils.c \
		utils/ms_tokens_utils.c \
		utils/ms_token_list_utils.c \
		utils/ms_echo_utils.c \
		utils/ms_envp_utils.c \
		builtins/ms_builtin_cd.c \
		builtins/ms_builtin_pwd.c \
		builtins/ms_builtin_env.c \
		builtins/ms_builtin_exit.c \
		builtins/ms_builtin_export.c \
		builtins/ms_builtin_unset.c \
		builtins/ms_builtin_echo.c \

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
OBJS_DEBUG := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%_debug.o,$(SRCS))

all: $(OBJS_DIR) $(NAME)

debug: CFLAGS += $(CFLAGS_DEBUG)

debug: $(OBJS_DIR) $(OBJS_DEBUG) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_DEBUG) $(LIBFT) -o $(NAME) -lreadline
	@echo "MINISHELL (Debug version) is ready!"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "MINISHELL is ready!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADR) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(OBJS_DIR)/%_debug.o: $(SRCS_DIR)/%.c $(HEADR) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I./includes -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "Cleaning..."

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Full cleaning..."

re: fclean all

.PHONY: all clean fclean re
