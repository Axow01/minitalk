/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mick <mick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:30:09 by mick              #+#    #+#             */
/*   Updated: 2023/02/26 09:44:38 by mick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_check_length(int *length, char **phrase, int sender_pid)
{
	if (*length <= 0)
	{
		*length = 0;
		ft_printf("%s", *phrase);
		*phrase = ft_free(*phrase);
		kill(sender_pid, SIGUSR1);
	}
}

void	ft_check_bit(int *current_bit, int *length, char **phrase,
		char **binary)
{
	*current_bit = 0;
	*phrase = ft_add_char(*phrase, ft_print_converted_binary(*binary));
	*binary = ft_free(*binary);
	*length -= 1;
}
