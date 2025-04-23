/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:44:01 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/23 03:39:02 by sede-san         ###   ########.fr       */
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

# define SIG_BIT0 SIGUSR1
# define SIG_BIT1 SIGUSR2

# define SLEEP_TIME 42/1000

#endif
