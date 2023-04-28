/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:35:53 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/28 19:10:44 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

typedef struct con_s
{
	char			*str;
	int				pid;
	int				index;
	int				tick;
}					t_con;

typedef struct rec_s
{
	char	c;
	int		count;
	int		len;
	int		i;
	char	*str;
	int		pid;
}			t_rec;

// This function write a message then quit the program.
void				ft_error(char *message, int exitn);

// This function handle the signal sent by the client.
void				ft_handler(int signal, siginfo_t *info, void *context);

// This function check the pid of the client.
int					ft_check_pid(int received_pid, t_rec *data);

#endif
