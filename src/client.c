/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:41 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/18 17:01:54 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

#define CHUNK_SIZE 500

con_t	con;

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
	}
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_printf("\033[32;1mMessage received !");
		exit(0);
	}
    else
        ft_send_message(con.str, con.pid);
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
	struct sigaction	sa;

	if (argc != 3)
		ft_error("Usage: ./client <serverpid> <message>, not that hard men.\n",
					1);
	con.pid = atoi(argv[1]);
	con.str = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_send_len(con.pid, con.str);
	usleep(100);
	ft_send_message(con.str, con.pid);
	while(1)
	{
		pause();
	}
}
