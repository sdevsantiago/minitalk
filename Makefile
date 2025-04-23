# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 21:23:43 by sede-san          #+#    #+#              #
#    Updated: 2025/04/23 02:48:18 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

SERVER = server
CLIENT = client

# ************************** Compilation variables *************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

# ********************************** Utils *********************************** #

MAKE += --no-print-directory

# ******************************* Compilation ******************************** #

SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ****************************** Source files ******************************** #

SRC_PATH = src

SERVER_PATH = $(SRC_PATH)/server

SERVER_SRC = \
	$(PATH_SERVER)/server.c

CLIENT_PATH = $(SRC_PATH)/client

CLIENT_SRC = \
	$(PATH_CLIENT)/client.c

# ********************************** Rules *********************************** #

all: libft ft_printf
	$(MAKE) server client

server: $(SRC_SERVER)
	$(CC) $(SRC_SERVER) $(LIBFT_PATH)/libft.a $(FT_PRINTF_PATH)/libftprintf.a -o $(SERVER_NAME)

client: $(SRC_CLIENT)
	$(CC) $(SRC_CLIENT) $(LIBFT_PATH)/libft.a $(FT_PRINTF_PATH)/libftprintf.a -o $(CLIENT_NAME)

clean:
	clean:
	if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) clean; \
	fi
	if [ -d $(LIBFTPRINTF_PATH) ]; then \
		$(MAKE) -C $(LIBFTPRINTF_PATH) clean; \
	fi

fclean: clean
	rm -rf $(LIB_PATH)

re: fclean all

# ******************************* Libraries ********************************** #

LIB_PATH = lib

LIBFT_PATH = $(LIB_PATH)/Libft

LIBFT = $(LIBFT_PATH)/libft.a

libft:
	if [ ! -d $(LIBFT_PATH) ]; then \
		git clone https://github.com/sdevsantiago/Libft.git $(LIBFT_PATH); \
		$(MAKE) -C $(LIBFT_PATH) all bonus; \
	elif [ ! -f $(LIBFT) ]; then \
		$(MAKE) -C $(LIBFT_PATH) re bonus; \
	else \
		cd $(LIBFT_PATH); \
		git pull; \
		cd -; \
	fi

LIBFTPRINTF_PATH = $(LIB_PATH)/ft_printf

LIBFTPRINTF = $(LIBFTPRINTF_PATH)/libftprintf.a

ft_printf:
	if [ ! -d $(LIBFTPRINTF_PATH) ]; then \
		git clone https://github.com/sdevsantiago/ft_printf.git $(LIBFTPRINTF_PATH); \
		$(MAKE) -C $(LIBFTPRINTF_PATH) all; \
	elif [ ! -f $(LIBFTPRINTF) ]; then \
		$(MAKE) -C $(LIBFTPRINTF_PATH) re; \
	else \
		cd $(LIBFTPRINTF_PATH); \
		git pull; \
		cd -; \
	fi
