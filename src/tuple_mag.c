/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_mag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:49:22 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	tuple_mag(t_tuple u)
{
	double	r;

	r = u.s_xyzw.x * u.s_xyzw.x;
	r += u.s_xyzw.y * u.s_xyzw.y;
	r += u.s_xyzw.z * u.s_xyzw.z;
	r += u.s_xyzw.w * u.s_xyzw.w;
	return (sqrt(r));
}
