/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:44:01 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/30 20:36:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../lib/Libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <signal.h>
# include <bits/sigaction.h>

# define SOH '\001'
# define ETB '\017'
# define STX '\002'
# define ETX '\003'
# define SYN '\026'
# define ACK '\006'
# define EOT '\004'

# define BYTE_SIZE 8

// Server signals
# define SIG_BIT0 SIGUSR1
# define SIG_BIT1 SIGUSR2

// Client signals
# define SIG_ACK SIGUSR1
# define SIG_MSGOK SIGUSR2

// // typedef struct	s_minitalk
// // {
	// // __pid_t	current_client;
	// // t_list	*client_queue;
// // }				t_minitalk;

typedef	struct	s_minitalk
{
	__pid_t	client_pid;
	int		bits_remaining;
	char	character_received;
	char	*message;
}				t_minitalk;

/*********************************** Utils ************************************/

t_minitalk	*mt_new(__pid_t client_pid);
char		*ft_gnl_strjoin(char *s1, const char *s2);
void		mt_free(void *node);

/****************************** Inline functions ******************************/

static inline t_minitalk	*mt_clientdata(t_list *clients)
{
	return ((t_minitalk *)(clients->content));
}

#endif
