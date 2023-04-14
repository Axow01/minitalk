/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:10:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 16:18:36 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>

# define WAIT_TIME 100

void	ft_send_bits(char c, int pid);
void	ft_error_handling(char *error, char *code);
void	ft_check_pid(char *pid, char *message);
void	ft_check_length(int *length, char **phrase, int sender_pid);
char	*ft_add_char(char *str, char c);
int		ft_print_converted_binary(char *binary);
void	ft_check_bit(int *current_bit, int *length, char **phrase,
			char **binary);

#endif