/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:00:00 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 21:40:36 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float calculate_A_cylinder(t_vector D)
{
    return (D.x * D.x) + (D.z * D.z);
}

float calculate_B_cylinder(t_vector D, t_vector cylinder_center, t_vector ray_origin)
{
    return 2 * ((D.x * (ray_origin.x - cylinder_center.x)) +
                (D.z * (ray_origin.z - cylinder_center.z)));
}

float calculate_C_cylinder(t_vector cylinder_center, t_vector ray_origin, float radius)
{
    float dx = ray_origin.x - cylinder_center.x;
    float dz = ray_origin.z - cylinder_center.z;
    return (dx * dx) + (dz * dz) - (radius * radius);
}
float compute_cylinder_intersection(t_ray ray, t_cylinder cyl)
{
    t_vector ca = normalize_vector(cyl.axis);
    t_vector oc = subtract_vectors(ray.b, cyl.center);

    // Remove axis component to get perpendicular projection
    t_vector rd_proj = subtract_vectors(ray.D, multiply_vector_by_scalar(ca, dot_product(ray.D, ca)));
    t_vector oc_proj = subtract_vectors(oc, multiply_vector_by_scalar(ca, dot_product(oc, ca)));

    float A = dot_product(rd_proj, rd_proj);
    float B = 2 * dot_product(rd_proj, oc_proj);
    float radius = cyl.diameter * 0.5f;
    float C = dot_product(oc_proj, oc_proj) - (radius * radius);

    float discriminant = B * B - 4 * A * C;
    if (discriminant < 0)
        return -1.0f;

    float sqrt_disc = sqrtf(discriminant);
    float t1 = (-B - sqrt_disc) / (2 * A);
    float t2 = (-B + sqrt_disc) / (2 * A);

    float t = -1.0f;
    if (t1 > 0.0001f)
        t = t1;
    else if (t2 > 0.0001f)
        t = t2;

    if (t < 0)
        return -1.0f;

    // Check if the hit is within the cylinder height
    t_vector hit = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t));
    float dist_along_axis = dot_product(subtract_vectors(hit, cyl.center), ca);

    if (dist_along_axis < 0.0f || dist_along_axis > cyl.height)
        return -1.0f;

    return t;
}
