/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:30:51 by mmarcott          #+#    #+#             */
/*   Updated: 2023/04/14 22:29:04 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char    *ft_add_char(char c, char *string)
{
    int i;
    char *new;

    new = ft_calloc(ft_strlen(string) + 2, sizeof(char));
    if (!new)
        return(NULL);
    i = 0;
    while (string && string[i])
    {
        new[i] = string[i];
        i++;
    }
    new[i++] = c;
    new[i] = 0;
    string = ft_free(string);
    return (new);
}
