/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/29 21:06:45 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void mt_msghandler(int signum, siginfo_t *info, void *ptr);

int main(void)
{
	struct sigaction msghandler;

	msghandler.sa_sigaction = mt_msghandler;
	msghandler.sa_flags = SA_SIGINFO;
	sigemptyset(&msghandler.sa_mask);
	sigaction(SIG_BIT0, &msghandler, NULL);
	sigaction(SIG_BIT1, &msghandler, NULL);
	ft_putstr("Server started with "UNDERLINE"PID"NO_UNDERLINE" ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
	{
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles transmission signals
 *
 * @attention ptr is not used in this function.
 * @note `SIG_BIT0` is `SIGUSR1` and `SIG_BIT1` is `SIGUSR2`
 */
void mt_msghandler(int signum, siginfo_t *info, void *ptr)
{
	static char	character_received;
	static int	bits_remaining;

	(void)ptr;
	if (bits_remaining <= 0)
		bits_remaining = BYTE_SIZE;
	if (signum == SIG_BIT0)
		character_received = character_received << 1;
	else
		character_received = (character_received << 1) | 1;
	kill(info->si_pid, SIG_ACK);
	if (--bits_remaining == 0)
	{
		if (character_received == '\0')
		{
			ft_putchar('\n');
			ft_printf("PID: %d\n", info->si_pid);
			kill(info->si_pid, SIG_MSGOK);
		}
		else
			ft_putchar(character_received);
		character_received = 0;
	}
}
