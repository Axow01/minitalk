/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:40:09 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/18 17:02:00 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_error(char *message, int exitn)
{
	ft_printf("%s", message);
    exit(exitn);
}

void    ft_send_message(char *str, int pid)
{
    static int  i = 0;

    if (str[i])
        ft_send_byte(str[i++], pid);
}
