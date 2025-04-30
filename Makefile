# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 21:23:43 by sede-san          #+#    #+#              #
#    Updated: 2025/04/30 13:47:26 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

SERVER = server
CLIENT = client

# ************************** Compilation variables *************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG), lldb)
	CFLAGS += -g3
else ifeq  ($(DEBUG), fsanitize)
	CFLAGS += -fsanitize=address
endif

# ********************************** Utils *********************************** #

MAKE += --no-print-directory

# ******************************* Compilation ******************************** #

SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ****************************** Source files ******************************** #

SRC_PATH = src

SERVER_SRC = \
	$(SRC_PATH)/server.c

CLIENT_SRC = \
	$(SRC_PATH)/client.c

# ********************************** Rules *********************************** #

all: libft ft_printf server client
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) $(LIBFTPRINTF) -o $(SERVER)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) $(LIBFTPRINTF) -o $(CLIENT)

server: $(SERVER_OBJ)

client: $(CLIENT_OBJ)

clean:
	if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) clean; \
	fi
	if [ -d $(LIBFTPRINTF_PATH) ]; then \
		$(MAKE) -C $(LIBFTPRINTF_PATH) clean; \
	fi
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean: clean
	rm -rf $(LIB_PATH)
	rm -f $(SERVER)
	rm -f $(SERVER_PATH)/$(SERVER).a
	rm -f $(CLIENT)
	rm -f $(CLIENT_PATH)/$(CLIENT).a

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
