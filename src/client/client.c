/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:07 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/15 18:46:19 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"

void showbits( unsigned int x )
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

void	mt_txcharacter(const char c, int pid);

int main(int argc, char const *argv[])
{
	int server_pid;
	char *message;

	if (argc < 3)
	{
		ft_putstr_fd("ERROR: Not enough arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	message = ft_strdup(argv[2]);
	if (!ft_strncmp(message, "stfu server", ft_strlen("stfu server")))
	{
		printf("Shutting server\n");
		kill(server_pid, SIGINT);
		return (EXIT_SUCCESS);
	}
	while (*message)
	{
		mt_txcharacter(*message, server_pid);
		message++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Sends a character `c` to the process `pid` bit by bit.
 *
 * @param c The character to send
 * @param pid The PID of the reciever
 *
 * @details This function shifts and sends each bit of the character passed
 *
 * @note SIG_BIT0 is SIGUSR1 and SIG_BIT1 is SIGUSR2
 */
void	mt_txcharacter(const char c, int pid)
{
	short	bits_remaining;
	short	bit;

	bits_remaining = 8;
	while (--bits_remaining >= 0)
	{
		bit = c >> bits_remaining & 1;
		if (bit == 1)
			kill(pid, SIG_BIT1);
		else
			kill(pid, SIG_BIT0);												//? For testing
		usleep(100);
	}
}
