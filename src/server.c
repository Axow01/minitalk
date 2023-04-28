/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/28 18:22:16 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_len(int signal, int *len, char **str, int pid)
{
	static int	count_int = 0;
	static int	c = 0;

	if (signal == SIGUSR2)
		c = (c >> 1) | (1 << 31);
	else if (signal == SIGUSR1)
		c = (c >> 1) & ~(1 << 31);
	if (count_int == 31)
	{
		*len = c;
		*str = ft_calloc(c + 1, sizeof(char));
		count_int = 0;
		c = 0;
		usleep(100);
		kill(pid, SIGUSR2);
		return ;
	}
	count_int++;
}

void	ft_check_message_len(int pid, int *len, int *i, char **str)
{
	if (*i == *len)
	{
		*i = 0;
		*len = 0;
		ft_printf("%s", *str);
		write(1, "\n", 1);
		*str = ft_free(*str);
		kill(pid, SIGUSR1);
	}
}

void	ft_assign(int signal, char *c)
{
	if (signal == SIGUSR2)
		*c = (*c >> 1) | 0x80;
	else if (signal == SIGUSR1)
		*c = (*c >> 1) & 0x7F;
}

void	ft_receive(int signal, siginfo_t *info, void *context)
{
	static char	c = 0x80;
	static int	count = 0;
	static int	len = 0;
	static int	i = 0;
	static char	*str = NULL;

	(void)context;
	if (len <= 0)
	{
		ft_len(signal, &len, &str, info[0].si_pid);
	}
	else if (info[0].si_pid != 0 && len > 0)
	{
		ft_assign(signal, &c);
		if (count == 7)
		{
			count = -1;
			str[i++] = c;
			c = 0x80;
			ft_check_message_len(info[0].si_pid, &len, &i, &str);
		}
		count++;
		kill(info[0].si_pid, SIGUSR2);
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
