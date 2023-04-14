/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:42 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 17:14:35 by mmarcott         ###   ########.fr       */
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
		usleep(WAIT_TIME);
		i++;
	}
}

void	ft_send_bits(char c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
		{
			ft_printf("1");
			kill(pid, SIGUSR2);
		}
		else
		{
			ft_printf("0");
			kill(pid, SIGUSR1);
		}
		c = c >> 1;
		usleep(WAIT_TIME);
	}
	ft_printf("\n");
}

void	ft_receive_confirmation(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Message received!");
		exit(0);
	}
	else if(signal == SIGUSR2)
	{
		ft_printf("Bytes received.\n");
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	*message;
	int		pid;
	int		count;
	int		sizee;

	message = argv[2];
	signal(SIGUSR1, ft_receive_confirmation);
	signal(SIGUSR2, ft_receive_confirmation);
	ft_printf("%d\n", argc);
	if (argc != 3)
		return (ft_error_handling("The args are wrong!", "001"), 0);
	ft_check_pid(argv[1], message);
	pid = ft_atoi(argv[1]);
	i = 0;
	count = 1;
	sizee = ft_strlen(message);
	//exit(0);
	ft_send_strlen(message, pid);
	while (message[i])
    {
        ft_send_bits(message[i++], pid);
		pause();
		usleep(WAIT_TIME);
        ft_printf("Sent: %d\n", sizee - count++);
    }
	//while (1)
		//pause();
	return (0);
}
