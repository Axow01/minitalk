/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:48 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/20 13:02:45 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
SIGUSR1 = 0
SIGUSR2 = 1
bit 0 - 7
00000000

*/

void	ft_print_converted_binary(char *binary)
{
	int	i;
	int	base;
	int	dec;

	i = ft_strlen(binary) - 1;
	base = 1;
	dec = 0;
	while (i > 0)
	{
		if (binary[i] == '1')
			dec += base;
		base *= 2;
		i--;
	}
	ft_printf("%c", dec, (char)dec);
}

void	ft_receiving(int signal)
{
	static char	*binary;

	if (signal == SIGUSR2)
		binary = ft_strjoin("1", binary);
	else if (signal == SIGUSR1)
		binary = ft_strjoin("0", binary);
	if (ft_strlen(binary) >= 8)
	{
		ft_print_converted_binary(binary);
		binary = ft_free(binary);
	}
}

int	main(void)
{
	int pid = (int)getpid();
	ft_printf("Server is starting PID is: %d\n", pid);
	signal(SIGUSR1, ft_receiving);
	signal(SIGUSR2, ft_receiving);
	while (1)
		usleep(WAIT_TIME);
}