/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:20:14 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/24 15:43:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned int     ft_swap_int(unsigned int n)
{
    int     swap;

    swap = ((n >> 24) & 0xFF)\
        | ((n >> 8) & 0xFF00)\
        | ((n << 8) & 0xFF0000)\
        | ((n << 24) & 0xFF000000);
    return (swap);
}
