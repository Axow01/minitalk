/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:35:53 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/15 16:59:32 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

typedef struct      chunk_s
{
    char            *chunk;
    struct chunk_s  *next;
}       chunk_t;

// This function write a message then quit the program.
void	ft_error(char *message, int exitn);
// This function add a char at the end of a string.
char    *ft_add_char(char c, char *string);
// Sends bytes to the server.
void	ft_send_byte(char c, int pid);
// Sends a message.
int ft_send_message(char *message, int pid);

void	ft_handler(int signal, siginfo_t *info, void *context);

void    ft_send_chunks(chunk_t *chunk, int pid);

#endif
