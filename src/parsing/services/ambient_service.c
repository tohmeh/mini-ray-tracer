/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_service.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:37:11 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/19 18:08:28 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	parts_size(char **line_parts)
{
	int	length;

	length = 0;
	while (line_parts[length])
	{
		length++;
	}
	return (length);
}

int	validate_ambient_lighting(char **line_parts)
{
	if (parts_size(line_parts) != 3)
		error_exit("ambient light must have 3 fields");
	if (!validate_id(line_parts[0], "A", 1))
		error_exit("invalid ambient light id");
	if (!validate_ratio(line_parts[1]))
		error_exit("ratio [0.0,1.0]");
	if (!validate_colors(line_parts[2]))
		error_exit("colors in range [0,255]");
	return (1);
}

t_ambient	*init_ambient(float ratio, t_color color)
{
	t_ambient	*ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		return (NULL);
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
}

t_ambient	*parse_ambient(char **line_parts)
{
	t_ambient	*ambient;
	float		ratio;
	t_color		color;

	if (!validate_ambient_lighting(line_parts))
		return (NULL);
	ratio = get_float(line_parts[1]);
	color = get_color(line_parts[2]);
	ambient = init_ambient(ratio, color);
	return (ambient);
}
