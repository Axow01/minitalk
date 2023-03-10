/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mick <mick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:48 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/26 09:44:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_print_converted_binary(char *binary)
{
	int	i;
	int	base;
	int	dec;

	i = ft_strlen(binary) - 1;
	base = 1;
	dec = 0;
	while (i >= 0)
	{
		if (binary[i] == '1')
			dec += base;
		base *= 2;
		i--;
	}
	return (dec);
}

char	*ft_add_char(char *str, char c)
{
	int		i;
	char	*newstring;

	i = 0;
	newstring = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!newstring)
		return (NULL);
	while (str && str[i])
	{
		newstring[i] = str[i];
		i++;
	}
	newstring[i++] = c;
	newstring[i] = 0;
	return (str = ft_free(str), newstring);
}

void	ft_receive_strlen(char **binary, int *length, int signal)
{
	static int	current_bit_deux = 0;

	if (signal == SIGUSR2)
		*binary = ft_strjoin("1", *binary);
	else if (signal == SIGUSR1)
		*binary = ft_strjoin("0", *binary);
	if (current_bit_deux == 31)
	{
		current_bit_deux = 0;
		*length = ft_print_converted_binary(*binary);
		*binary = ft_free(*binary);
		return ;
	}
	current_bit_deux++;
}

void	ft_receiving(int signal, siginfo_t *info, void *context)
{
	static char	*binary = NULL;
	static int	current_bit = 0;
	static int	lenght = 0;
	static char	*phrase = NULL;
	int			sender_pid;

	(void)context;
	sender_pid = info[0].si_pid;
	if (lenght == 0)
		ft_receive_strlen(&binary, &lenght, signal);
	else
	{
		if (signal == SIGUSR2)
			binary = ft_strjoin("1", binary);
		else if (signal == SIGUSR1)
			binary = ft_strjoin("0", binary);
		if (current_bit == 7)
		{
			ft_check_bit(&current_bit, &lenght, &phrase, &binary);
			ft_check_length(&lenght, &phrase, sender_pid);
			return ;
		}
		current_bit++;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = (int)getpid();
	ft_printf("\033[1;33mPID: \033[0;36m%d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receiving;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
