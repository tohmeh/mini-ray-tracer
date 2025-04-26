/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:46:06 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:52:25 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float	compute_sphere_intersection(t_vector ray_direction,
		t_vector sphere_center, t_vector ray_origin, float radius)
{
	t_vector	oc;
	float		b;
	float		discriminant;
	float		t;

	oc = subtract_vectors(ray_origin, sphere_center);
	b = 2 * dot_product(ray_direction, oc);
	discriminant = (b * b) - 4 * (dot_product(oc, oc) - radius * radius);
	if (discriminant < 0)
		return (-1.0f);
	discriminant = sqrtf(discriminant);
	t = (-b - discriminant) / 2;
	if (t > 0)
		return (t);
	t = (-b + discriminant) / 2;
	if (t > 0)
		return (t);
	return (-1.0f);
}
