/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/31 17:39:42 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void		mt_msghandler(int signal, siginfo_t *signal_info, void *clients);
t_minitalk	*mt_new(__pid_t client_pid);

void		_reallocmsg(t_minitalk **client);

/**
 * @brief Minitalk's server program.
 */
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
	ft_printf("Server started with "UNDERLINE"PID"NO_UNDERLINE" %d\n",
		getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles incoming bits and prints the message when all characters have
 * been received.
 *
 * @attention `context` is not used in this function.
 *
 * @param signal The signal to handle.
 * @param signal_info Additional information about the sender.
 * @param context Additional information about the process execution when
 * `signal` was received.
 *
 * @note `SIG_BIT0` = `SIG_ACK` = `SIGUSR1`
 * @note `SIG_BIT1` = `SIG_MSGOK` = `SIGUSR2`
 */
void	mt_msghandler(int signal, siginfo_t *signal_info, void *context)
{
	static t_minitalk	*client;

	(void)context;
	if (!client)
		client = mt_new(signal_info->si_pid);
	if (!client->bits_remaining)
		client->bits_remaining = BYTE_SIZE;
	if (signal == SIG_BIT0)
		client->char_received <<= 1;
	else
		client->char_received = (client->char_received << 1) | 1;
	kill(client->pid, SIG_ACK);
	if (!--(client->bits_remaining))
	{
		if (client->char_received == '\0')
		{
			ft_printf(BOLD"Message:"RESET"\t%s\n", client->message);
			ft_printf(BOLD"PID:"RESET"\t\t%d\n", client->pid);
			kill(client->pid, SIG_MSGOK);
			ft_free((void *)&client->message);
			ft_free((void *)&client);
		}
		else
			_reallocmsg(&client);
	}
}

/**
 * @brief Appends the character received to the message sent by the client.
 *
 * @param client_msg The message sent by the client.
 *
 * @note This function is auxiliar to `mt_msghandler`.
 */
void	_reallocmsg(t_minitalk **client)
{
	char	*tmp_msg;
	size_t	i;

	if ((*client)->message)
		tmp_msg = ft_calloc(ft_strlen((*client)->message) + 2, sizeof(char));
	else
		tmp_msg = ft_calloc(2, sizeof(char));
	i = 0;
	while ((*client)->message && (*client)->message[i])
	{
		tmp_msg[i] = (*client)->message[i];
		i++;
	}
	tmp_msg[i] = (*client)->char_received;
	ft_free((void *)&(*client)->message);
	(*client)->message = tmp_msg;
}

/**
 * @brief Allocates memory for a new incoming message.
 *
 * @param client_pid The PID of the client sending the message.
 */
t_minitalk	*mt_new(__pid_t client_pid)
{
	t_minitalk	*new_client;

	new_client = (t_minitalk *)ft_calloc(1, sizeof(t_minitalk));
	if (!new_client)
		return (NULL);
	new_client->pid = client_pid;
	return (new_client);
}
