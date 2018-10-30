/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 15:15:43 by sfranc            #+#    #+#             */
/*   Updated: 2018/10/30 10:36:00 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

void	ft_puthexa_16(unsigned long long nbr)
{
	const char	hex[16] = "0123456789abcdef";
	char		s[16];
	int			i;

	i = 0;
	ft_memset(s, '0', 16);
	while (nbr != 0)
	{
		s[i++] = hex[nbr % 16];
		nbr /= 16;
	}
	i = 16;
	while (i--)
		ft_putchar(s[i]);
}