/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:30:51 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/28 19:13:15 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_error(char *message, int exitc)
{
	ft_printf("%s\n", message);
	exit(exitc);
}

int	ft_check_pid(int received_pid, t_rec *data)
{
	if (received_pid == data->pid)
		return (1);
	data->c = 0;
	data->count = 0;
	data->i = 0;
	data->len = 0;
	data->pid = 0;
	data->str = ft_free(data->str);
	return (0);
}
