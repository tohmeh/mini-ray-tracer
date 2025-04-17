/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:46:06 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/29 01:16:54 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float calculate_A_sphere(t_vector D)
{
    return dot_product(D, D);
}

float calculate_B_sphere(t_vector D, t_vector sphere_center, t_vector ray_origin)
{
    t_vector OC = subtract_vectors(ray_origin, sphere_center);
    return 2 * dot_product(D, OC);
}

float calculate_C_sphere(t_vector sphere_center, t_vector ray_origin, float radius)
{
    t_vector OC = subtract_vectors(ray_origin, sphere_center);
    return dot_product(OC, OC) - (radius * radius);
}

float compute_sphere_intersection(t_vector ray_direction, t_vector sphere_center, t_vector ray_origin, float radius)
{
    float A = dot_product(ray_direction, ray_direction);
    t_vector OC = subtract_vectors(ray_origin, sphere_center);
    float B = 2 * dot_product(ray_direction, OC);
    float C = dot_product(OC, OC) - (radius * radius);

    float discriminant = (B * B) - (4 * A * C);

    if (discriminant < 0)
        return -1.0; 
    
    float t1 = (-B - sqrtf(discriminant)) / (2 * A);
    float t2 = (-B + sqrtf(discriminant)) / (2 * A);

    if (t1 > 0) 
        return t1; 
    if (t2 > 0) 
        return t2; 

    return -1.0f; 
}