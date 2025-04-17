/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:01:56 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 13:00:04 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_sphere(char **line_parts)
{
	if (parts_size(line_parts) != 4)
		error_exit("sphere must have 4 fields");
	if (!validate_id(line_parts[0], "sp", 2))
		error_exit("invaled sphere Id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid coordinates");
	if (!ft_is_number(line_parts[2]))
		error_exit("invalid diameter");
	if (!validate_colors(line_parts[3]))
		error_exit("invalid colors [0,255]");
	return (1);
}

static t_sphere	*init_sphere(t_vector center, t_color color, float diameter)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->color = color;
	sphere->radius = diameter / 2;
	sphere->next = NULL;
	return (sphere);
}

t_sphere	*parse_sphere(char **line_parts)
{
	t_sphere	*sphere;
	t_vector	center;
	t_color		color;
	float		diameter;

	if (!validate_sphere(line_parts))
		return (0);
	center = get_vector(line_parts[1]);
	diameter = get_float(line_parts[2]);
	color = get_color(line_parts[3]);
	sphere = init_sphere(center, color, diameter);
	return (sphere);
}
