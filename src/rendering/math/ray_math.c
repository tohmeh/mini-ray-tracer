/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 01:58:49 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/17 22:34:16 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

#ifndef M_PI
#define M_PI 3.14
#endif

t_ray generate_ray(t_camera *camera, int i, int j)
{
    t_ray ray;

    float fov_rad = camera->fov * M_PI / 180.0;
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float scale = tan(fov_rad / 2);
    
    float pixel_x = (2 * ((i + 0.5) / WIDTH) - 1) * aspect_ratio * scale;
    float pixel_y = (1 - 2 * ((j + 0.5) / HEIGHT)) * scale;
    
    t_vector right = compute_right_vector(camera->direction);
    t_vector up = cross_product(camera->direction, right);
    
    t_vector ray_dir;
    ray_dir.x = pixel_x * right.x + pixel_y * up.x + camera->direction.x;
    ray_dir.y = pixel_x * right.y + pixel_y * up.y + camera->direction.y;
    ray_dir.z = pixel_x * right.z + pixel_y * up.z + camera->direction.z;
    
    ray_dir = normalize_vector(ray_dir);
    
    ray.D = ray_dir;
    ray.b = camera->position;
    
    return ray;
}