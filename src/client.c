/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:41 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 22:21:58 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int		confirmation_received = 0;

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_printf("Message received.");
		exit(0);
	}
	else
		confirmation_received = 1;
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
	struct sigaction	sa;
	int					i;

	if (argc != 3)
		ft_error("Usage: ./client <serverpid> <message>, not that hard men.\n",
					1);
	message = argv[2];
	pid = (pid_t)ft_atoi(argv[1]);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	ft_send_len(pid, message);
	usleep(100);
	while (message[i])
	{
		ft_send_byte(message[i++], pid);
		while (!confirmation_received)
			pause();
		write(1, "☑\n", 5);
		confirmation_received = 0;
	}
	while(1)
		pause();
}
