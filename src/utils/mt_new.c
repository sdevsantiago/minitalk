/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:46:43 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/30 20:44:48 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

t_minitalk	*mt_new(__pid_t client_pid)
{
	t_minitalk	*new_client;

	new_client = (t_minitalk *)ft_calloc(1, sizeof(t_minitalk));
	if (!new_client)
		return (NULL);
	new_client->client_pid = client_pid;
	return (new_client);
}
