/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:54:58 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/12 12:53:59 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rt.h"
#include "object.h"

t_light	point_light_new(t_point location, t_color intensity)
{
	t_light	light;

	light.type = POINT;
	light.intensity = intensity;
	light.location = location;
	return (light);
}

t_light	sun_light_new(t_point direction, t_color intensity)
{
	t_light	light;

	light.type = SUN;
	light.intensity = intensity;
	light.direction = direction;
	return (light);
}
