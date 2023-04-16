/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:40:09 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/15 23:03:52 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int confirmation_received = 0;

void	ft_error(char *message, int exitn)
{
	ft_printf("%s", message);
    exit(exitn);
}

void    ft_send_chunks(chunk_t *chunk, int pid)
{
    chunk_t *current;
    int i;

    i = 1;
    current = chunk;
    while(current->next)
    {
        ft_send_message(current->chunk, pid);
        current = current->next;
    }
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_printf("Message received.");
		exit(0);
	}
	else
		confirmation_received = 1;
}

int ft_send_message(char *message, int pid)
{
    int                 i;

    i = 0;
    while(message[i])
    {
        ft_send_byte(message[i++], pid);
        pause();
    }
    return (1);
}
