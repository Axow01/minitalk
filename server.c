/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:48 by mmarcott          #+#    #+#             */
/*   Updated: 2023/01/19 17:29:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
SIGUSR1 = 0
SIGUSR2 = 1
bit 0 - 7
00000000

*/

void	signal_handler(int signal)
{
}

int	main(void)
{
	conv_to_base_print('a', 2, "01");
}