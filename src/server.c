/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 22:29:51 by mmarcott         ###   ########.fr       */
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

void	ft_len(int signal, int *len, char **bytes)
{
	static int	count_int = 0;

	if (signal == SIGUSR2)
		*bytes = ft_strjoin("1", *bytes);
	else if (signal == SIGUSR1)
		*bytes = ft_strjoin("0", *bytes);
	if (count_int == 31)
	{
        *len = ft_convert_binary(*bytes);
		*bytes = ft_free(*bytes);
		count_int = 0;
		return ;
	}
	count_int++;
}

void	ft_check_message_len(char *string, int pid, int *len)
{
	if ((int)ft_strlen(string) == *len)
	{
		*len = 0;
		ft_printf("%s", string);
		string = ft_free(string);
		kill(pid, SIGUSR1);
	}
}

void	ft_receive(int signal, siginfo_t *info, void *context)
{
	static char	*bytes = NULL;
	static int	count = 0;
	static int	len = 0;
	static char	*string = NULL;

	(void)context;
	if (len == 0)
		ft_len(signal, &len, &bytes);
	else
	{
		if (signal == SIGUSR2)
			bytes = ft_strjoin("1", bytes);
		else if (signal == SIGUSR1)
			bytes = ft_strjoin("0", bytes);
		if (count == 7)
		{
			count = 0;
			string = ft_add_char((char)ft_convert_binary(bytes), string);
			bytes = ft_free(bytes);
			ft_check_message_len(string, info[0].si_pid, &len);
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
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
}
