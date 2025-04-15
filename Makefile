# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 21:23:43 by sede-san          #+#    #+#              #
#    Updated: 2025/04/15 15:54:58 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME = server
CLIENT_NAME = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

# ******************************** Compilation ******************************* #

PATH_SRC = src

PATH_SERVER = $(PATH_SRC)/server
SRC_SERVER = \
	$(PATH_SERVER)/server.c

PATH_CLIENT = $(PATH_SRC)/client
SRC_CLIENT = \
	$(PATH_CLIENT)/client.c

# ********************************** Rules *********************************** #

all: libft ft_printf
	$(MAKE) server client

server: $(SRC_SERVER)
	$(CC) $(SRC_SERVER) $(LIBFT_PATH)/libft.a $(FT_PRINTF_PATH)/libftprintf.a -o $(SERVER_NAME)

client: $(SRC_CLIENT)
	$(CC) $(SRC_CLIENT) $(LIBFT_PATH)/libft.a $(FT_PRINTF_PATH)/libftprintf.a -o $(CLIENT_NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

RM = rm -rf
fclean:
	$(RM) $(LIB_PATH)
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

re: fclean all

# ******************************** Libraries ********************************* #

LIB_PATH = lib

LIBFT_PATH = $(LIB_PATH)/Libft
libft:
	git clone git@github.com:sdevsantiago/Libft.git $(LIBFT_PATH)
	$(MAKE) -C lib/Libft all bonus clean

FT_PRINTF_PATH = $(LIB_PATH)/ft_printf
ft_printf:
	git clone git@github.com:sdevsantiago/ft_printf.git $(FT_PRINTF_PATH)
	$(MAKE) -C lib/ft_printf all clean
