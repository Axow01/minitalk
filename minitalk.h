/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mick <mick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:10:12 by mmarcott          #+#    #+#             */
/*   Updated: 2023/02/25 20:11:11 by mick             ###   ########.fr       */
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

#endif