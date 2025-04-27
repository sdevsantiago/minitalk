/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/27 23:02:10 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void mt_msghandler(int signum);

int main(void)
{
	struct sigaction msghandler;

	msghandler.sa_handler = mt_msghandler;
	msghandler.sa_flags = 0;
	sigemptyset(&msghandler.sa_mask);
	int pid = getpid();
	ft_printf("Server started with "UNDERLINE"PID"NO_UNDERLINE" %d\n", pid);
	while (1)
	{
		if (sigaction(SIG_BIT0, &msghandler, NULL) == -1 ||
			sigaction(SIG_BIT1, &msghandler, NULL) == -1)
		{
			ft_putendl_fd("ERROR: An error ocurred, shutting down",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		sleep(2);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles transmission signals
 *
 * @note SIG_BIT0 is SIGUSR1 and SIG_BIT1 is SIGUSR2
 */
void mt_msghandler(int signum)
{
	static char	character_received;
	static int	bits_remaining;
	static int	msg_printed;
	static int	client_pid;

	if (bits_remaining <= 0)
		bits_remaining = sizeof(unsigned long) * BYTE_SIZE;
	if (signum == SIG_BIT0)
		character_received = character_received << 1;
	else
		character_received = (character_received << 1) + 1;
	if (--bits_remaining == 0)
	{
		if (!msg_printed)
		{
			if (character_received == STX)
				ft_putstr("Message: [");
			else if (character_received == ETX)
			{
				ft_putendl("]");
				msg_printed = 1;
			}
			else
				ft_putchar(character_received);
		}
		else
		{
			if (character_received == STX)
			{
				ft_putstr("PID: [");
				client_pid = 0;
			}
			else if (character_received == ETX)
			{
				ft_putendl("]");
				msg_printed = 0;
				kill(client_pid, SIGUSR2);
			}
			else
			{
				ft_putchar(character_received);
				client_pid = client_pid * 10 + ft_atoi(&character_received);
			}
		}

	}
}
