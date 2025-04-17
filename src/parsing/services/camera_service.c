/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:28:21 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 15:56:22 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_camera(char **line_parts)
{
	if (parts_size(line_parts) != 4)
		error_exit("camera must have 4 fields");
	if (!validate_id(line_parts[0], "C", 1))
		error_exit("invalid camera Id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid camera coordinates");
	if (!validate_orientation_vector(line_parts[2]))
		error_exit("invalid orientation vector [-1,1]");
	if (!validate_hfield(line_parts[3]))
		error_exit("invalid horizontal field [0,180]");
	return (1);
}

static t_camera	*init_camera(t_vector position, t_vector direction, float fov)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->position = position;
	camera->direction = direction;
	camera->fov = fov;
	return (camera);
}

t_camera	*parse_camera(char **line_parts)
{
	t_camera	*camera;
	t_vector	position;
	t_vector	direction;
	float		fov;

	if (!validate_camera(line_parts))
		return (0);
	position = get_vector(line_parts[1]);
	direction = get_vector(line_parts[2]);
	fov = get_float(line_parts[3]);
	camera = init_camera(position, direction, fov);
	return (camera);
}
