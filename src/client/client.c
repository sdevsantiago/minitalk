/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:07 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/14 19:13:33 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"

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
	}
	else
	{
		printf("Sending %s\n", message);
		kill(server_pid, SIGSTARTTX);
		while (*message)
		{
			sleep(1);
			kill(server_pid, *message + 1000);
			message++;
		}
		kill(server_pid, SIGENDTX);
		printf("End of transmission\n");
	}

	return (EXIT_SUCCESS);
}

