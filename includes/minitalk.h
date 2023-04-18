/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:35:53 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/18 17:02:06 by mmarcott         ###   ########.fr       */
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

typedef struct      con_s
{
    char    *str;
    int     pid;
}       con_t;

// This function write a message then quit the program.
void	ft_error(char *message, int exitn);
// This function add a char at the end of a string.
char    *ft_add_char(char c, char *string);
// Sends bytes to the server.
void	ft_send_byte(char c, int pid);
// Sends a message.
void    ft_send_message(char *str, int pid);

void	ft_handler(int signal, siginfo_t *info, void *context);

#endif
