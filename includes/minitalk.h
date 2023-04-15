/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:35:53 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 21:38:39 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

// This function write a message then quit the program.
void	ft_error(char *message, int exitn);
// This function add a char at the end of a string.
char    *ft_add_char(char c, char *string);

#endif
