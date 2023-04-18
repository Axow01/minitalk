/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/18 17:00:44 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_convert_binary(char *binary)
{
	int	base;
	int	dec;
	int	i;

	i = ft_strlen(binary) - 1;
	dec = 0;
	base = 1;
	while (i >= 0)
	{
		if (binary[i] == '1')
			dec += base;
		base *= 2;
		i--;
	}
	return (dec);
}

void ft_len(int signal, int *len) {
    static int count_int = 0;
    static int c = 0;

    if (signal == SIGUSR2) {
        c = (c >> 1) | (1 << 31); // shift right and set the leftmost bit to 1
    } else if (signal == SIGUSR1) {
        c = (c >> 1) & ~(1 << 31); // shift right and set the leftmost bit to 0
    }

    if (count_int == 31) {
        *len = c;
        count_int = 0;
        c = 0; // reset the counter for the next message
    } else {
        count_int++;
    }
}

void	ft_check_message_len(char **string, int pid, int *len, int *i)
{
	if (*i == *len)
	{
		*i = 0;
		*len = 0;
		ft_printf("%s\n", *string);
		*string = ft_free(*string);
		kill(pid, SIGUSR1);
	}
}


void	ft_receive(int signal, siginfo_t *info, void *context)
{
	static char c = 0x80;
	static int	count = 0;
	static int	len = 0;
	static int	i = 0;
	static char	*string = NULL;

	(void)context;
	if (len == 0)
	{
		ft_len(signal, &len);
	}
	else
	{
		if (!string)
			string = ft_calloc(len + 1, sizeof(char));
		if (signal == SIGUSR2)
			c = (c >> 1) | 0x80; // shift right and set the leftmost bit to 1
		else if (signal == SIGUSR1)
			c = (c >> 1) & 0x7F;
		if (count == 7)
		{
			count = 0;
			string[i++] = c;
			c = 0x80;
			ft_check_message_len(&string, info[0].si_pid, &len, &i);
			kill(info[0].si_pid, SIGUSR2);
			return ;
		}
		count++;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receive;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("\033[33;1;4mPID:\033[0m \033[36m%d\n\033[0m", getpid());
	while (1)
		pause();
}
