/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:03:32 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 15:29:27 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_desimal_div(int count)
{
	double	ret;

	ret = 1.0;
	while (count != 0)
	{
		ret *= 10;
		count--;
	}
	return (ret);
}

double	ft_atof(char *line_arg_r)
{
	int		i;
	int		count;
	double	r;
	double	negative;

	negative = 1.0f;
	r = 0.0;
	i = 0;
	count = 1;
	if (line_arg_r[i] == '-')
	{
		negative = -1.0f;
		i++;
	}
	while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
	{
		r += ((double)line_arg_r[i] - '0');
		if ((double)line_arg_r[++i] >= '0' && (double)line_arg_r[i] <= '9')
			r *= 10.0;
	}
	if (line_arg_r[i++] == '.')
		while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
			r += ((double)line_arg_r[i++] - '0') / get_desimal_div(count++);
	return (r * (double)negative);
}
