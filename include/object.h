/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/06 15:48:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "rt.h"
# include "tuple.h"
# include "vector.h"

typedef struct s_object
{
	t_vec3			loc;
	t_vec3			coi;
	t_vec3			up;
	t_vec3			rot;
	double			size;
	double			brightness;
	int				type;
	union u_tuple	color;
}					t_object;

typedef struct s_abc
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_abc;

#endif