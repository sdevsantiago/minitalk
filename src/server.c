/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/30 21:35:46 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief The list where all the messages of all the clients will be stored.
 */
t_list				*g_clients;

void	mt_msghandler(int signal, siginfo_t *signal_info, void *clients);
void	mt_closehandler(int signal);

int	main(void)
{
	struct sigaction	msghandler;
	struct sigaction	closehandler;

	msghandler.sa_sigaction = mt_msghandler;
	msghandler.sa_flags = SA_SIGINFO;
	sigemptyset(&msghandler.sa_mask);
	sigaddset(&msghandler.sa_mask, SIG_BIT0);
	sigaddset(&msghandler.sa_mask, SIG_BIT1);
	sigaction(SIG_BIT0, &msghandler, NULL);
	sigaction(SIG_BIT1, &msghandler, NULL);
	closehandler.sa_handler = mt_closehandler;
	closehandler.sa_flags = 0;
	sigemptyset(&closehandler.sa_mask);
	sigaction(SIGINT, &closehandler, NULL);
	sigaction(SIGTERM, &closehandler, NULL);
	sigaction(SIGSEGV, &closehandler, NULL);
	g_clients = NULL;
	ft_putstr("Server started with "UNDERLINE"PID"NO_UNDERLINE" ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles incoming bits and prints the message when all characters have
 * been received.
 *
 * @param signal The signal to handle.
 * @param signal_info Additional information about the sender.
 * @param context Additional information about the process execution when
 * `signal` was received.
 *
 * @attention `context` is not used in this function.
 *
 * @note `SIG_BIT0` = `SIG_ACK` = `SIGUSR1`
 * @note `SIG_BIT1` = `SIG_MSGOK` = `SIGUSR2`
 */
void	mt_msghandler(int signal, siginfo_t *signal_info, void *context)
{
	t_list		*current;

	(void)context;
	current = g_clients;
	while (current
		&& mt_clientdata(current)->client_pid != signal_info->si_pid)
		current = current->next;
	if (!current)
	{
		ft_lstadd_back(&g_clients, ft_lstnew(mt_new(signal_info->si_pid)));
		current = ft_lstlast(g_clients);
		if (!current)
		{
			ft_putendl(RED_TEXT"ERROR: Invalid malloc, exiting"RESET);
			exit(EXIT_FAILURE);
		}
	}
	if (!mt_clientdata(current)->bits_remaining)
		mt_clientdata(current)->bits_remaining = BYTE_SIZE;
	if (signal == SIG_BIT0)
		mt_clientdata(current)->character_received <<= 1;
	else
		mt_clientdata(current)->character_received =
			(mt_clientdata(current)->character_received << 1) | 1;
	kill(mt_clientdata(current)->client_pid, SIG_ACK);
	if (!--(mt_clientdata(current)->bits_remaining))
	{
		if (mt_clientdata(current)->character_received == '\0')
		{
			ft_printf(BOLD"Message:"RESET"\t%s\n"BOLD"PID:"RESET"\t\t%d\n",
				mt_clientdata(current)->message,
				mt_clientdata(current)->client_pid);
			kill(mt_clientdata(current)->client_pid, SIG_MSGOK);
			ft_lstdelone(current, mt_free);
		}
		else
			mt_clientdata(current)->message =
				ft_gnl_strjoin(mt_clientdata(current)->message,
				&mt_clientdata(current)->character_received);
	}
}
// // void	mt_msghandler(int signal, siginfo_t *info, void *ptr)
// // {
// // 	static __pid_t	current_client_pid = 0;
// // 	static char		character_received = 0;
// // 	static int		bits_remaining = BYTE_SIZE;

// // 	(void)ptr;
// // 	if (current_client_pid != 0 && info->si_pid != current_client_pid)
// // 		return ;
// // 	if (current_client_pid == 0)
// // 		current_client_pid = info->si_pid;
// // 	if (signal == SIG_BIT0)
// // 		character_received <<= 1;
// // 	else
// // 		character_received = (character_received << 1) | 1;
// // 	kill(info->si_pid, SIG_ACK);
// // 	if (--bits_remaining == 0)
// // 	{
// // 		if (character_received == '\0')
// // 		{
// // 			ft_printf("\nPID: %d\n", info->si_pid);
// // 			kill(info->si_pid, SIG_MSGOK);
// // 			current_client_pid = 0;
// // 		}
// // 		else
// // 			ft_putchar(character_received);
// // 		character_received = 0;
// // 		bits_remaining = BYTE_SIZE;
// // 	}
// // }

void	mt_closehandler(int signal)
{
	ft_putstr(BOLD);
	ft_putstr(RED_TEXT);
	ft_putchar('\r');
	if (signal == SIGINT)
		ft_putstr("Received SIGINT. ");
	else if (signal == SIGTERM)
		ft_putstr("Received SIGTERM. ");
	ft_putendl("Shutting down server.");
	ft_putstr(RESET);
	ft_lstclear(&g_clients, mt_free);
	if (signal == SIGSEGV)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
