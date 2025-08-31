# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 20:22:21 by sede-san          #+#    #+#              #
#    Updated: 2025/08/31 17:59:28 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

SERVER_NAME	= server
CLIENT_NAME	= client

# ************************** Compilation variables *************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
HEADERS	= -I $(INCLUDE_PATH) -I $(LIBFT_INCLUDE_PATH) -I $(FT_PRINTF_INCLUDE_PATH)

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

MAKE += --no-print-directory

# ****************************** Source files ******************************** #

SRC_PATH = src

SERVER_SRC = $(SRC_PATH)/server.c

CLIENT_SRC = $(SRC_PATH)/client.c

INCLUDE_PATH = include

# ****************************** Object files ******************************** #

OBJS_PATH	= build
SERVER_OBJS	= $(SERVER_SRC:$(SRC_PATH)/%.c=$(OBJS_PATH)/%.o)
CLIENT_OBJS	= $(CLIENT_SRC:$(SRC_PATH)/%.c=$(OBJS_PATH)/%.o)

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$< compiled"

# ********************************* Rules ************************************ #

all: libft ft_printf server client
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT_BIN) $(FT_PRINTF_BIN) -o $(SERVER_NAME)
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT_BIN) $(FT_PRINTF_BIN) -o $(CLIENT_NAME)
.PHONY: all

server: $(SERVER_OBJS)

client: $(CLIENT_OBJS)

clean:
	@rm -rf $(OBJS_PATH)
.PHONY: clean

fclean: clean
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)
	@if [ -d $(LIBFT_PATH) ]; then									\
		$(MAKE) --silent -C $(LIBFT_PATH) fclean > /dev/null;		\
	fi
	@if [ -d $(FT_PRINTF_PATH) ]; then								\
		$(MAKE) --silent -C $(FT_PRINTF_PATH) fclean > /dev/null;	\
	fi
.PHONY: fclean

re: fclean all
.PHONY: re

# ****************************** Libraries ********************************** #

LIB_PATH = lib

# ** Libft ** #

LIBFT				= Libft
LIBFT_REPO			= https://github.com/sdevsantiago/Libft.git
LIBFT_PATH			= $(LIB_PATH)/$(LIBFT)
LIBFT_INCLUDE_PATH	= $(LIBFT_PATH)
LIBFT_BIN			= $(LIBFT_PATH)/libft.a

libft: $(LIBFT_BIN)
.PHONY: libft

$(LIBFT_BIN):
	@if [ ! -d $(LIBFT_PATH) ]; then									\
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(LIBFT)...$(RESET)";	\
		git clone --quiet $(LIBFT_REPO) $(LIBFT_PATH);					\
		rm -rf $(LIBFT_PATH)/.git;										\
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) cloned...$(RESET)";		\
	fi
	@if [ ! -f $(LIBFT_BIN) ]; then										\
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(LIBFT)...$(RESET)";	\
		$(MAKE) --silent -C $(LIBFT_PATH) all clean;					\
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) compiled.$(RESET)";		\
	fi

# ** ft_printf **

FT_PRINTF				= ft_printf
FT_PRINTF_REPO			= https://github.com/sdevsantiago/ft_printf.git
FT_PRINTF_PATH			= $(LIB_PATH)/$(FT_PRINTF)
FT_PRINTF_INCLUDE_PATH	= $(FT_PRINTF_PATH)/include
FT_PRINTF_BIN			= $(FT_PRINTF_PATH)/libftprintf.a

ft_printf: $(FT_PRINTF_BIN)
.PHONY: ft_printf

$(FT_PRINTF_BIN):
	@if [ ! -d $(FT_PRINTF_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(FT_PRINTF)...$(RESET)";	\
		git clone --quiet $(FT_PRINTF_REPO) $(FT_PRINTF_PATH);				\
		rm -rf $(FT_PRINTF_PATH)/.git;										\
		echo "$(GREEN)$(EMOJI_CHECK) $(FT_PRINTF) cloned...$(RESET)";		\
	fi
	@if [ ! -f $(FT_PRINTF_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(FT_PRINTF)...$(RESET)";					\
		$(MAKE) --silent -C $(FT_PRINTF_PATH) all clean LIBFT_PATH=../$(LIBFT) > /dev/null;	\
		echo "$(GREEN)$(EMOJI_CHECK) $(FT_PRINTF) compiled.$(RESET)";						\
	fi

# ***************************** Style variables ****************************** #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

EMOJI_BROOM = 🧹
EMOJI_CHECK = ✅
EMOJI_CROSS = ❌
EMOJI_WRENCH = 🔧
EMOJI_BOX = 📦
