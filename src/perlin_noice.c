/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:43:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 16:27:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	load_perlin_data(t_perlin *perlin)
{
	FILE	*fp;
	int		permutation[256];
	int		i;

	if (!(perlin->is_data_writen))
	{
		i = 0;
		fp = fopen("include/perlindata.txt", "r");
		if (fp == NULL)
			return (0);
		while (i < 256)
			fscanf(fp, "%d", &permutation[i++]);
		//!!!!!!!!!!!! DO WE USE FSCAN OR DO WE NEED TO CONWERT TO SOMETHING ELSE!!!!
		fclose(fp);
		i = 0;
		while (i < 256)
		{
			perlin->p[i] = permutation[i];
			perlin->p[256 + i] = permutation[i];
			i++;
		}
	}
	return (1);
}

double	calculate_return(t_tuple p, t_perlin *perlin)
{
	double	temp;
	double	temp_a;
	double	temp_b;
	double	temp_c;

	temp = lerp(perlin->u, grad(perlin->p[perlin->ab + 1],
				p.s_xyzw.x, p.s_xyzw.y - 1, p.s_xyzw.z - 1),
			grad(perlin->p[perlin->bb + 1], p.s_xyzw.x - 1,
				p.s_xyzw.y - 1, p.s_xyzw.z - 1));
	temp_a = lerp(perlin->v, lerp(perlin->u,
				grad(perlin->p[perlin->aa + 1], p.s_xyzw.x, p.s_xyzw.y,
					p.s_xyzw.z - 1), grad(perlin->p[perlin->ba + 1],
					p.s_xyzw.x - 1, p.s_xyzw.y, p.s_xyzw.z - 1)), temp);
	temp_b = lerp(perlin->u, grad(perlin->p[perlin->ab], p.s_xyzw.x,
				p.s_xyzw.y - 1, p.s_xyzw.z), grad(perlin->p[perlin->bb],
				p.s_xyzw.x - 1, p.s_xyzw.y - 1, p.s_xyzw.z));
	temp_c = lerp(perlin->w, lerp(perlin->v, lerp(perlin->u,
					grad(perlin->p[perlin->aa], p.s_xyzw.x,
						p.s_xyzw.y, p.s_xyzw.z),
					grad(perlin->p[perlin->ba], p.s_xyzw.x - 1,
						p.s_xyzw.y, p.s_xyzw.z)), temp_b), temp_a);
	return (temp_c);
}

double	perlin_noice(t_tuple point, t_perlin *perlin)
{
	perlin->x_i = (int)floor(point.s_xyzw.x) & 255;
	perlin->y_i = (int)floor(point.s_xyzw.y) & 255;
	perlin->z_i = (int)floor(point.s_xyzw.z) & 255;
	point.s_xyzw.x -= floor(point.s_xyzw.x);
	point.s_xyzw.y -= floor(point.s_xyzw.y);
	point.s_xyzw.z -= floor(point.s_xyzw.z);
	perlin->u = fade(point.s_xyzw.x);
	perlin->v = fade(point.s_xyzw.y);
	perlin->w = fade(point.s_xyzw.z);
	
	perlin->a = perlin->p[perlin->x_i] + perlin->y_i;
	perlin->aa = perlin->p[perlin->a] + perlin->z_i;
	// printf("hello %d %d %d\n", perlin->a, perlin->p[perlin->a], perlin->z_i);
	perlin->ab = perlin->p[perlin->a + 1] + perlin->z_i;
	perlin->b = perlin->p[perlin->x_i + 1] + perlin->y_i;
	perlin->ba = perlin->p[perlin->b] + perlin->z_i;
	perlin->bb = perlin->p[perlin->b + 1] + perlin->z_i;
	return (calculate_return(point, perlin));
}
