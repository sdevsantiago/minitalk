/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:44:01 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/31 17:39:59 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include "ft_printf.h"
# include <signal.h>
# include <errno.h>

# define BYTE_SIZE 8

// Server signals

# define SIG_BIT0 SIGUSR1
# define SIG_BIT1 SIGUSR2

// Client signals

# define SIG_ACK SIGUSR1
# define SIG_MSGOK SIGUSR2

typedef struct s_minitalk
{
	__pid_t	pid;
	int		bits_remaining;
	char	char_received;
	char	*message;
}				t_minitalk;

#endif /* MINITALK_H */
