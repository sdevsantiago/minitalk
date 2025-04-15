/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/04/15 18:43:58 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define UNDERLINE "\033[4m"
#define	NO_UNDERLINE "\033[24m"

#include "../../include/server.h"

char	*ft_gnl_strjoin(char *s1, const char *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc(sizeof (*joined) * (s1_len + s2_len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	free((void *)s1);
	return (joined);
}

void mt_txhandler(int signum);
void mt_serverloop(void);
void mt_closehandler(void);

int main(int argc, char const *argv[])
{
	// Transmission
	struct sigaction tx;
	// Close
	struct sigaction close;

	tx.sa_handler = mt_txhandler;
	tx.sa_flags = 0;
	sigemptyset(&tx.sa_mask);
	sigaction(SIG_BIT0, &tx, NULL);
	sigaction(SIG_BIT1, &tx, NULL);

	close.sa_handler = mt_closehandler;
	close.sa_flags = 0;
	sigemptyset(&close.sa_mask);
	sigaction(SIGINT, &close, NULL);
	sigaction(SIGTERM, &close, NULL);
	// // sigaction(SIGKILL, &close, NULL);

	printf("Server started with "UNDERLINE"PID"NO_UNDERLINE" %d\n", getpid());

	mt_serverloop();
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles transmission signals
 *
 * @note SIG_BIT0 is SIGUSR1 and SIG_BIT1 is SIGUSR2
 */
void mt_txhandler(int signum)
{
	static char		*message;
	static char		character_received;
	static short	bits_remaining;

	if (!bits_remaining)
		bits_remaining = 8;
	if (signum == SIG_BIT0)
		character_received = character_received << 1;
	else
		character_received = (character_received << 1) + 1;
	if (--bits_remaining == 0)
	{
		ft_putchar(character_received);
	}
}

void mt_serverloop(void)
{
	while (1)
	{
	}
}

void mt_closehandler(void)
{
	printf("\rTerminating process\n");
	exit(EXIT_SUCCESS);
}
