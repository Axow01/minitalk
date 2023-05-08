/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:41 by mmarcott          #+#    #+#             */
/*   Updated: 2023/05/08 18:14:42 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_con	g_con = {NULL, 0, 0, 0};

void	ft_send_byte(char c, int i)
{
	usleep(20);
	c = c >> i;
	if (c & 1)
	{
		kill(g_con.pid, SIGUSR2);
	}
	else
	{
		kill(g_con.pid, SIGUSR1);
	}
}

void	ft_send_message(char *str)
{
	static int	i = 0;
	static int	stri = 0;

	if (i == 8)
	{
		i = 0;
		stri++;
	}
	if (!str[stri])
		return ;
	ft_send_byte(str[stri], i++);
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_con.tick = 0;
	if (signal == SIGUSR1)
		ft_error("\033[32;1mMessage delivered successfully.\033[0m\n", 0);
	else if (signal == SIGUSR2)
		ft_send_message(g_con.str);
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

/* Here we initialise our variable g_con. And we sends
 the first bit to the server. */
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		ft_error("Usage: ./client <serverpid> <message>, not that hard men.\n",
			1);
	if (argv[2][0] == 0)
		ft_error("Your message is empty ?", 1);
	g_con.pid = ft_atoi(argv[1]);
	g_con.str = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_send_len(g_con.pid, g_con.str);
	while (1)
	{
		if (g_con.tick++ >= 100000)
			ft_error("Faillure time out..\n", 1);
		usleep(10);
	}
}
