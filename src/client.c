/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:07 by sede-san          #+#    #+#             */
/*   Updated: 2025/05/02 20:43:27 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Signal received by server acknowledgement.
 *
 * @warning This variable MUST NOT be modified by any function as this can lead
 * to unexpected behaviour.
 */
volatile sig_atomic_t	g_ack;

void	mt_sendchar(char c, int pid);
void	mt_anshandler(int signum);

void	_ack(int signum);

/**
 * @brief Minitalk's client program.
 */
int	main(int argc, char const *argv[])
{
	__pid_t	server_pid;

	if (argc < 3)
		return (ft_putstr_fd(RED_TEXT"ERROR: Not enough arguments\n"RESET,
				STDERR_FILENO), EXIT_FAILURE);
	g_ack = 0;
	signal(SIG_MSGOK, mt_anshandler);
	signal(SIG_ACK, _ack);
	server_pid = ft_atoi(argv[1]);
	while (*argv[2])
	{
		mt_sendchar(*argv[2], server_pid);
		argv[2]++;
	}
	mt_sendchar('\0', server_pid);
	pause();
	return (EXIT_SUCCESS);
}

/**
 * @brief Sends the character `c` to the server running at `pid`.
 *
 * @param c The character to send
 * @param pid The server's PID
 *
 * @details This function sends a char bit by bit, left to right, so that the
 * server can then "build" the character sent. After each bit is sent, the
 * server sends a confirmation that allows this function to send another bit.
 */
void	mt_sendchar(char c, int pid)
{
	short	bits_remaining;
	int		sig_sent;

	bits_remaining = BYTE_SIZE;
	while (--bits_remaining >= 0)
	{
		if ((c >> bits_remaining) & 1)
			sig_sent = kill(pid, SIG_BIT1);
		else
			sig_sent = kill(pid, SIG_BIT0);
		if (sig_sent == -1)
		{
			if (errno == ESRCH)
				ft_putendl(RED_TEXT"ERROR: No such process"RESET);
			else
				ft_putendl(RED_TEXT"ERROR: Unknown error"RESET);
			exit(EXIT_FAILURE);
		}
		while (!g_ack)
			usleep(50);
		g_ack = 0;
	}
}

/**
 * @brief Handles the `SIG_ACK` signal to override `g_ack` value.
 *
 * @attention `signum` is not used in this function.
 *
 * @param signum The signal received.
 *
 * @note `SIG_ACK` = `SIGUSR1`
 */
void	_ack(int signum)
{
	(void)signum;
	g_ack = 1;
}

/**
 * @brief Handles the `SIG_MSGOK` signal to exit the program.
 *
 * @attention `signum` is not used in this function.
 *
 * @param signum The signal received.
 *
 * @note `SIG_MSGOK` = `SIGUSR2`
 */
void	mt_anshandler(int signum)
{
	(void)signum;
	ft_putendl(GREEN_TEXT
		"Server has received and printed the message"
		RESET);
	exit(EXIT_SUCCESS);
}
