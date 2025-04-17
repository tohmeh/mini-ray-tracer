/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+        */
/*   Created: 2025/03/27 23:30:00 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/27 23:30:00 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float calculate_denominator(t_vector plane_normal, t_vector ray_direction)
{
    return dot_product(plane_normal, ray_direction);
}

float calculate_numerator(t_vector plane_normal, t_vector plane_point, t_vector ray_origin)
{
    t_vector P0_O = subtract_vectors(plane_point, ray_origin);
    return dot_product(plane_normal, P0_O);
}

float compute_plane_intersection(t_vector plane_normal, t_vector plane_point, 
                                 t_vector ray_direction, t_vector ray_origin)
{
    float denominator = calculate_denominator(plane_normal, ray_direction);

    if (fabs(denominator) < 0)
        return -1;

    float numerator = calculate_numerator(plane_normal, plane_point, ray_origin);
    float t = numerator / denominator;

	if (t)
		return (t);
	else
		return (-1);
}
