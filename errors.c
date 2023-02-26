/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mick <mick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:03:45 by mick              #+#    #+#             */
/*   Updated: 2023/02/25 20:13:07 by mick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_check_pid(char *pid, char *message)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit((int)pid[i++]))
			ft_error_handling("Error the pid is wrong..", "001");
	}
	if (message[0] == '\0')
		ft_error_handling("Error the message is empty..", "002");
}
