# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 21:23:43 by sede-san          #+#    #+#              #
#    Updated: 2025/04/14 21:37:51 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************** Libraries ********************************* #

libft:
	git clone git@github.com:sdevsantiago/Libft.git lib/Libft
	$(MAKE) -C lib/Libft all bonus clean

ft_printf:
	git clone git@github.com:sdevsantiago/ft_printf.git lib/ft_printf
	$(MAKE) -C lib/ft_printf all clean
