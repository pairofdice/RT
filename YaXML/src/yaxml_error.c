/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:31:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/21 15:31:29 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

int	xml_error_free(t_buffers *buf, char *err_str)
{
	if (err_str != NULL)
	{
		ft_putstr_fd("ERROR: ", 2);
		ft_putendl_fd(err_str, 2);
	}
	free(buf->mem);
	return (FALSE);
}

int	xml_return_error(const char *str)
{
	ft_putendl_fd(str, 2);
	return (FALSE);
}
