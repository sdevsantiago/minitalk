/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:44:01 by sede-san          #+#    #+#             */
/*   Updated: 2025/05/01 03:27:16 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../lib/Libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <signal.h>

# define BYTE_SIZE 8

// Server signals
# define SIG_BIT0 SIGUSR1
# define SIG_BIT1 SIGUSR2

// Client signals
# define SIG_ACK SIGUSR1
# define SIG_MSGOK SIGUSR2

typedef	struct	s_minitalk
{
	__pid_t	client_pid;
	int		bits_remaining;
	char	character_received;
	char	*message;
}				t_minitalk;

/*********************************** Utils ************************************/

t_minitalk	*mt_new(__pid_t client_pid);
void		mt_free(void *node);

/****************************** Inline functions ******************************/

static inline t_minitalk	*mt_clientdata(t_list *clients)
{
	return ((t_minitalk *)(clients->content));
}

#endif /* MINITALK_H */
