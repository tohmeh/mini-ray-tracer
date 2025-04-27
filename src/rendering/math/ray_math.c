/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 01:58:49 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:54:54 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

#ifndef M_PI
# define M_PI 3.14
#endif

// Fast inverse square root (from Quake III)
float fast_inv_sqrt(float number)
{
    union {
        float f;
        long i;
    } conv;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    conv.f = number;
    conv.i = 0x5f3759df - (conv.i >> 1);
    y = conv.f;
    y = y * (threehalfs - (x2 * y * y)); // First Newton step
    y = y * (threehalfs - (x2 * y * y)); // Second Newton step
    y = y * (threehalfs - (x2 * y * y)); // Second Newton step
    return y;
}


// Fast normalize
t_vector fast_normalize(t_vector v)
{
    float inv_len = fast_inv_sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    v.x *= inv_len;
    v.y *= inv_len;
    v.z *= inv_len;
    return v;
}
t_ray generate_ray(t_camera *camera, int i, int j)
{
    t_ray ray;
    float u, v;  // Normalized device coordinates
    
    // Calculate screen coordinates using cached values
    u = (i + 0.5f) * camera->params.pixel_dx - camera->params.aspect_ratio * camera->params.fov_tan_half;
    v = camera->params.fov_tan_half - (j + 0.5f) * camera->params.pixel_dy;
    
    // Calculate ray direction using cached vectors
    ray.d = (t_vector){
        u * camera->params.right_vector.x + v * camera->params.up_vector.x + camera->direction.x,
        u * camera->params.right_vector.y + v * camera->params.up_vector.y + camera->direction.y,
        u * camera->params.right_vector.z + v * camera->params.up_vector.z + camera->direction.z
    };
    
	// ray.d = normalize_v(ray.d);
    ray.d = fast_normalize(ray.d);
    ray.b = camera->position;
    
    return (ray);
}

