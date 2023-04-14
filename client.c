/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:42 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 18:13:47 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <wchar.h>

void	ft_error_handling(char *error, char *code)
{
	ft_printf("Error: %s\nCode: %s\n", error, code);
	ft_printf("The right usage is ./client <pidnumber:int> <message:string>");
	exit(1);
}

void	ft_send_strlen(char *message, int pid)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(message);
	while (i < 32)
	{
		if (length & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		length = length >> 1;
		i++;
		usleep(WAIT_TIME);
	}
}

void	ft_send_bits(char c, int pid)
{
	int	i;

	i = -1;
	ft_printf("%c\n", c);
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		if (i + 1 == 8)
			return ;
		c = c >> 1;
		usleep(WAIT_TIME);
	}
}

void	ft_receive_confirmation(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_printf("Message received!");
		exit(0);
	}
	else if (signal == SIGUSR2)
	{
		return ;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	char				*message;
	int					pid;
	int					count;
	int					sizee;
	struct sigaction	sa;

	message = argv[2];
	ft_printf("%d\n", argc);
	if (argc != 3)
		return (ft_error_handling("The args are wrong!", "001"), 0);
	ft_check_pid(argv[1], message);
	pid = ft_atoi(argv[1]);
	i = 0;
	count = 1;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receive_confirmation;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sizee = ft_strlen(message);
	//exit(0);
	ft_send_strlen(message, pid);
	while (message[i])
	{
		ft_send_bits(message[i++], pid);
		pause();
	}
	while (1)
		pause();
	return (0);
}
