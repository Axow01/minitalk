/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:41 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/15 22:49:59 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

#define CHUNK_SIZE 500

void	ft_chunk(chunk_t *chunk, char *message)
{
	int	i;
	int	b;
	int	c;
	int	n_chunk;
	chunk_t	*current;

	i = 0;
	b = 0;
	(void)i;
	(void)chunk;
	n_chunk = ft_strlen(message) / CHUNK_SIZE + 1;
	current = chunk;
	ft_printf("%d\n\n", n_chunk);
	while (i < n_chunk)
	{
		current->chunk = ft_calloc(CHUNK_SIZE + 1, sizeof(char));
		if (!current->chunk)
			ft_error("Failed to allocate current.chunk.", 1);
		c = 0;
		while (message[b] && c <= CHUNK_SIZE)
			current->chunk[c++] = message[b++];
		current->chunk[c] = 0;
		if (i + 1 == n_chunk)
			break;
		current->next = ft_calloc(1, sizeof(chunk_t));
		if (!current->next)
			ft_error("Failed to allocate, the next node.", 1);
		current = current->next;
		i++;
	}
}

void	ft_send_byte(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		i++;
		usleep(100);
	}
}

void	ft_send_len(int pid, char *message)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(message);
	while (i < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	char				*message;
	pid_t				pid;
	chunk_t				*chunk;
	struct sigaction	sa;

	if (argc != 3)
		ft_error("Usage: ./client <serverpid> <message>, not that hard men.\n",
					1);
	message = argv[2];
	pid = (pid_t)ft_atoi(argv[1]);
	sa.sa_flags = SA_NODEFER;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_send_len(pid, message);
	usleep(100);
	if (ft_strlen(message) <= CHUNK_SIZE) // Check if the message need to be separated in chunks.
		ft_send_message(message, pid);
	else
	{
		chunk = ft_calloc(1, sizeof(chunk_t));
		ft_chunk(chunk, message);
		ft_send_chunks(chunk, pid);
	}
	while(1)
	{
		ft_printf("WAITING...");
		pause();
	}
}
