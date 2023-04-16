/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:32:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/15 23:02:54 by mmarcott         ###   ########.fr       */
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

void	ft_check_message_len(char **string, int pid, int *len)
{
	int leng;

	leng = (int)ft_strlen(*string);
	ft_printf("%d - %d\n", leng, *len);
	if (leng == *len)
	{
		*len = 0;
		ft_printf("%s", *string);
		*string = ft_free(*string);
		kill(pid, SIGUSR1);
	}
}

void print_char_bits(char c) {
  int i;

  for (i = 7; i >= 0; i--) {
    printf("%d", (c >> i) & 1);
  }
  printf("\n");
}

void	ft_receive(int signal, siginfo_t *info, void *context)
{
	static char c = 0x80;
	static char *bytes = NULL;
	static int	count = 0;
	static int	len = 0;
	static int	largemessage = 0;
	static char	*string = NULL;

	(void)context;
	if (len == 0)
		ft_len(signal, &len, &bytes);
	else
	{
		if (signal == SIGUSR2)
			c = (c >> 1) | 0x80; // shift right and set the leftmost bit to 1
		else if (signal == SIGUSR1)
			c = (c >> 1) & 0x7F;
		if (count == 7)
		{
			largemessage += 1;
			count = 0;
			string = ft_add_char(c, string);
			c = 0x80;
			ft_check_message_len(&string, info[0].si_pid, &len);
			kill(info[0].si_pid, SIGUSR2);
			return ;
		}/*
		if (largemessage >= 500)
		{
			largemessage = 0;
			kill(info[0].si_pid, SIGUSR2);
		}*/
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
