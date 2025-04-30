/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:12:41 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/30 20:56:43 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

void	mt_free(void	*node)
{
	t_minitalk	*client;

	client = node;
	client->bits_remaining = 0;
	client->character_received = 0;
	client->client_pid = 0;
	free(client->message);
}
