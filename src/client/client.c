/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:07 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/29 21:07:59 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	mt_txcharacter(char c, int pid);
void	mt_anshandler(int signum);
void	_continue(int signum);

int main(int argc, char const *argv[])
{
	int					server_pid;

	if (argc < 3)
		return (ft_putstr_fd("ERROR: Not enough arguments\n", STDERR_FILENO),
			EXIT_FAILURE);
	signal(SIG_MSGOK, mt_anshandler);
	signal(SIG_ACK, _continue);
	server_pid = ft_atoi(argv[1]);
	while (*argv[2])
	{
		mt_txcharacter(*argv[2], server_pid);
		argv[2]++;
	}
	mt_txcharacter('\0', server_pid);
	pause();
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
void	mt_txcharacter(char c, int pid)
{
	short	bits_remaining;

	bits_remaining = BYTE_SIZE;
	while (--bits_remaining >= 0)
	{
		if (c >> bits_remaining & 1)
			kill(pid, SIG_BIT1);
		else
			kill(pid, SIG_BIT0);
		pause();
	}
}

void	mt_anshandler(int signum)
{
	if (signum == SIG_MSGOK)
		ft_putendl(GREEN_TEXT
			"Server has received and printed the message"
			RESET);
	exit(EXIT_SUCCESS);
}

void	_continue(int signum)
{
	(void)signum;
}
