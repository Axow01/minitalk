/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:42 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/20 15:25:19 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error_handling(char *error, char *code)
{
	ft_printf("Error: %s\nCode: %s\n", error, code);
	ft_printf("The right usage is ./client <pidnumber:int> <message:string>");
}

void	ft_send_bits(char c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(WAIT_TIME);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	*message;
	int		pid;

	message = argv[2];
	i = 0;
	if (argc != 3)
		return (ft_error_handling("The args are wrong!", "001"), 0);
	while (argv[1][i])
	{
		if (!ft_isdigit((int)argv[1][i++]))
			return (ft_error_handling("The args[0] not a number!", "002"), 1);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("PID of the server is: %d\n", pid);
	i = 0;
	while (message[i])
		ft_send_bits(message[i++], pid);
	return (1);
}
