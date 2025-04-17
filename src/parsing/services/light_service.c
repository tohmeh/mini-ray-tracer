/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_service.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:48:32 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:59:58 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_light(char **line_parts)
{
	if (parts_size(line_parts) != 4)
		error_exit("light must have 4 fields");
	if (!validate_id(line_parts[0], "L", 1))
		error_exit("invalid light Id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid coordinates");
	if (!validate_ratio(line_parts[2]))
		error_exit("invalid ratio [0.0,1.0]");
	if (!validate_colors(line_parts[3]))
		error_exit("invalid colors range [0-255]");
	return (1);
}

static t_light	*init_light(float brightness, t_color color, t_vector position)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->brightness = brightness;
	light->color = color;
	light->position = position;
	light->next = NULL;
	return (light);
}

t_light	*parse_light(char **line_parts)
{
	t_light		*light;
	float		brightness;
	t_color		color;
	t_vector	position;

	if (!validate_light(line_parts))
		return (0);
	position = get_vector(line_parts[1]);
	brightness = get_float(line_parts[2]);
	color = get_color(line_parts[3]);
	light = init_light(brightness, color, position);
	return (light);
}
