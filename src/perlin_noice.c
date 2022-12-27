/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:43:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/20 15:06:11 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	free_mallocs(char *line, char **values)
{
	int	i;

	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
	free(line);
}

void	load_perlin_data(t_perlin *perlin)
{
	int			fd;
	char		*line;
	char		**values;
	int			i;

	i = 0;
	perlin->is_data_writen = TRUE;
	fd = open("include/perlindata.txt", O_RDONLY);
	if (perlin->is_data_writen != FALSE && fd < 0)
		perlin->is_data_writen = FALSE;
	if (get_next_line(fd, &line) < 0)
		perlin->is_data_writen = FALSE;
	close(fd);
	values = ft_strsplit(line, ' ');
	if (values[0] == NULL)
		perlin->is_data_writen = FALSE;
	while (perlin->is_data_writen == TRUE && i < 256 && values[i][0] != '\0')
	{
		fd = ft_atoi(values[i]);
		perlin->p[i] = fd;
		perlin->p[256 + i] = fd;
		i++;
	}
	free_mallocs(line, values);
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
	perlin->ab = perlin->p[perlin->a + 1] + perlin->z_i;
	perlin->b = perlin->p[perlin->x_i + 1] + perlin->y_i;
	perlin->ba = perlin->p[perlin->b] + perlin->z_i;
	perlin->bb = perlin->p[perlin->b + 1] + perlin->z_i;
	return (calculate_return(point, perlin));
}
