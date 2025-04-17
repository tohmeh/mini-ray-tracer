/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_service.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:11:28 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 16:54:48 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_plane(char **line_parts)
{
	if (parts_size(line_parts) != 4)
		error_exit("plane must have 4 fields");
	if (!validate_id(line_parts[0], "pl", 2))
		error_exit("invalid plane Id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid plane coordinates");
	if (!validate_orientation_vector(line_parts[2]))
		error_exit("invalid orientation vector  [-1,1]");
	if (!validate_colors(line_parts[3]))
		error_exit("invalid colors [0,255]");
	return (1);
}

static t_plane	*init_plane(t_color color, t_vector normal, t_vector point)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->color = color;
	plane->normal = normal;
	plane->point = point;
	plane->next = NULL;
	return (plane);
}

t_plane	*parse_plane(char **line_parts)
{
	t_plane		*plane;
	t_color		color;
	t_vector	normal;
	t_vector	point;

	if (!validate_plane(line_parts))
		return (0);
	point = get_vector(line_parts[1]);
	normal = get_vector(line_parts[2]);
	color = get_color(line_parts[3]);
	plane = init_plane(color, normal, point);
	return (plane);
}
