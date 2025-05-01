/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:07 by sede-san          #+#    #+#             */
/*   Updated: 2025/05/01 01:22:38 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

volatile sig_atomic_t	g_acknowledged;

void	mt_txcharacter(char c, int pid);
void	mt_anshandler(int signum);
void	_continue(int signum);

int	main(int argc, char const *argv[])
{
	__pid_t	server_pid;

	if (argc < 3)
		return (ft_putstr_fd(RED_TEXT"ERROR: Not enough arguments\n"RESET,
			STDERR_FILENO),	EXIT_FAILURE);
	g_acknowledged = 0;
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

void	mt_txcharacter(char c, int pid)
{
	short	bits_remaining;

	bits_remaining = BYTE_SIZE;
	while (--bits_remaining >= 0)
	{
		if ((c >> bits_remaining) & 1)
			kill(pid, SIG_BIT1);
		else
			kill(pid, SIG_BIT0);
		while (!g_acknowledged)
			usleep(50);
		g_acknowledged = 0;
	}
}

void	mt_anshandler(int signum)
{
	if (signum == SIG_MSGOK)
	{
		ft_putendl(GREEN_TEXT
			"Server has received and printed the message"
			RESET);
	}
	exit(EXIT_SUCCESS);
}

void	_continue(int signum)
{
	(void)signum;
	g_acknowledged = 1;
}
