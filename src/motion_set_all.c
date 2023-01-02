/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_set_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:43:31 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 15:17:33 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	set_camera_motions(t_cam *cam)
{
	int	motions_done;

	motions_done = 0;
	if (cam->motion.on_off == TRUE
		&& cam->motion.speed_iteration < cam->motion.speed)
	{
		cam->transform = motion_move(cam->transform, &cam->motion);
		motions_done++;
	}
	if (cam->coi_motion.on_off == TRUE
		&& cam->coi_motion.speed_iteration < cam->coi_motion.speed)
	{
		motion_move(cam->coi_transform, &cam->coi_motion);
		motions_done++;
	}
	return (motions_done);
}

int	motion_set_all(t_main *main)
{
	t_object	*obj;
	size_t		i;
	int			motions_done;

	i = 0;
	motions_done = 0;
	while (i < main->scene.objects.len)
	{
		obj = (t_object *)vec_get(&main->scene.objects, i);
		if (obj->motion.on_off == TRUE
			&& obj->motion.speed_iteration < obj->motion.speed)
		{
			obj->inverse_transform = motion_move(obj->inverse_transform,
					&obj->motion);
			motions_done++;
		}
		i++;
	}
	motions_done += set_camera_motions(&main->scene.cam);
	return (motions_done);
}
