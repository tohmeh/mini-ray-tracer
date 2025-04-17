/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vector_math.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:10:10 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/29 16:34:15 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector sphere_normal_vector(t_sphere sphere, t_vector intersection)
{
    t_vector N = subtract_vectors(intersection, sphere.center);
    return normalize_vector(N); // Ensure unit length
}

t_vector plane_normal_vector(t_plane plane)
{
    return normalize_vector(plane.normal); // Normalize the normal vector
}

t_vector cylinder_normal_vector(t_cylinder cylinder, t_vector intersection)
{
    t_vector to_point = subtract_vectors(intersection, cylinder.center);
    float projection_length = dot_product(to_point, cylinder.axis);
    t_vector projected_point = add_vectors(cylinder.center, multiply_vector_by_scalar(cylinder.axis, projection_length));

    t_vector normal = subtract_vectors(intersection, projected_point);
    return normalize_vector(normal);
}
