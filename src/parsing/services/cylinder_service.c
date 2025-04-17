/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:26:29 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 15:57:23 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_cylinder(char **line_parts)
{
	if (parts_size(line_parts) != 6)
		error_exit("must have 6 fields");
	if (!validate_id(line_parts[0], "cy", 2))
		error_exit("invalid id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid coordinates");
	if (!validate_orientation_vector(line_parts[2]))
		error_exit("invalid orientation vector");
	if (!ft_is_number(line_parts[3]))
		error_exit("invalid diameter");
	if (!ft_is_number(line_parts[4]))
		error_exit("invalid height");
	if (!validate_colors(line_parts[5]))
		error_exit("invalid colors");
	return (1);
}

static t_cylinder	*init_cylinder(t_vector axis, t_vector center,
		t_color color)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->axis = axis;
	cylinder->center = center;
	cylinder->color = color;
	cylinder->next = NULL;
	return (cylinder);
}

t_cylinder	*parse_cylinder(char **line_parts)
{
	t_cylinder	*cylinder;
	t_vector	center;
	t_vector	axis;
	t_color		color;

	if (!validate_cylinder(line_parts))
		return (0);
	center = get_vector(line_parts[1]);
	axis = get_vector(line_parts[2]);
	color = get_color(line_parts[5]);
	cylinder = init_cylinder(axis, center, color);
	cylinder->diameter = get_float(line_parts[3]);
	cylinder->height = get_float(line_parts[4]);
	return (cylinder);
}
