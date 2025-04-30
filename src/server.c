/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/30 18:48:20 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	mt_msghandler(int signum, siginfo_t *info, void *ptr);

int	main(void)
{
	struct sigaction	msghandler;

	msghandler.sa_sigaction = mt_msghandler;
	msghandler.sa_flags = SA_SIGINFO;
	sigemptyset(&msghandler.sa_mask);
	sigaddset(&msghandler.sa_mask, SIG_BIT0);
	sigaddset(&msghandler.sa_mask, SIG_BIT1);
	sigaction(SIG_BIT0, &msghandler, NULL);
	sigaction(SIG_BIT1, &msghandler, NULL);
	ft_putstr("Server started with "UNDERLINE"PID"NO_UNDERLINE" ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @attention `ptr` is not used in this function.
 *
 * @note `SIG_BIT0` = `SIG_ACK` = `SIGUSR1`
 * @note `SIG_BIT1` = `SIG_MSGOK` = `SIGUSR2`
 */
void	mt_msghandler(int signum, siginfo_t *info, void *ptr)
{
	static pid_t	current_client_pid;
	static char		character_received;
	static int		bits_remaining = BYTE_SIZE;

	(void)ptr;
	current_client_pid = 0;
	character_received = 0;
	if (current_client_pid != 0 && info->si_pid != current_client_pid)
		return ;
	if (current_client_pid == 0)
		current_client_pid = info->si_pid;
	if (signum == SIG_BIT0)
		character_received <<= 1;
	else
		character_received = (character_received << 1) | 1;
	kill(info->si_pid, SIG_ACK);
	if (--bits_remaining == 0)
	{
		if (character_received == '\0')
		{
			ft_printf("\nPID: %d\n", info->si_pid);
			kill(info->si_pid, SIG_MSGOK);
			current_client_pid = 0;
		}
		else
			ft_putchar(character_received);
		character_received = 0;
		bits_remaining = BYTE_SIZE;
	}
}
