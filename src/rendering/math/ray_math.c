/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 01:58:49 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:01:34 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

#ifndef M_PI
# define M_PI 3.14
#endif

t_ray	generate_ray(t_camera *camera, int i, int j)
{
	t_ray		ray;
	t_vector	right;
	float		pixel_x;
	float		pixel_y;

	pixel_x = (2 * ((i + 0.5) / (float)WIDTH) - 1) * ((float)WIDTH
			/ (float)HEIGHT) * tan((camera->fov * M_PI / 180.0) / 2);
	pixel_y = (1 - 2 * ((j + 0.5) / (float)HEIGHT)) * tan((camera->fov * M_PI
				/ 180.0) / 2);
	right = compute_right_vector(camera->direction);
	ray.D = normalize_vector((t_vector){pixel_x * right.x + pixel_y
			* cross_product(camera->direction, right).x + camera->direction.x,
			pixel_x * right.y + pixel_y * cross_product(camera->direction,
				right).y + camera->direction.y, pixel_x * right.z + pixel_y
			* cross_product(camera->direction, right).z + camera->direction.z});
	ray.b = camera->position;
	return (ray);
}
