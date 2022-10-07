/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:29:14 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/29 15:50:34 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_set_nb(long int *nb, int *neg)
{
	*nb *= -1;
	*neg = 1;
}

char	*ft_itoa(int n)
{
	char			*nbr_as_str;
	unsigned int	i;
	int				negative;
	long int		nb;

	nb = n;
	negative = 0;
	nbr_as_str = (char *)malloc(ft_nbrlen(n) + 1);
	if (nbr_as_str == NULL)
		return (NULL);
	i = 1;
	nbr_as_str[ft_nbrlen(n)] = '\0';
	if (nb < 0)
		ft_set_nb(&nb, &negative);
	while (i <= ft_nbrlen(n))
	{
		nbr_as_str[ft_nbrlen(n) - i] = '0' + (nb % 10);
		nb /= 10;
		i++;
	}
	if (negative)
		nbr_as_str[0] = '-';
	return (nbr_as_str);
}
