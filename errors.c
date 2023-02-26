/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mick <mick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:03:45 by mick              #+#    #+#             */
/*   Updated: 2023/02/26 09:29:59 by mick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_check_pid(char *pidd, char *message)
{
	int		i;
	char	*pid;

	pid = pidd;
	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit((int)pid[i++]))
			ft_error_handling("The args[0] not a number!", "002");
		if (message[0] == '\0')
			ft_error_handling("The message is empty, not sending.", "003");
	}
}
