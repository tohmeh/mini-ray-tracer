/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:43 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:07:09 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	get_cylinder_projection(t_vector v, t_vector axis)
{
	return (subtract_vectors(v, multiply_vector_by_scalar(axis, dot_product(v,
					axis))));
}

int	solve_quadratic(t_vector t
		, float *t1, float *t2)
{
	float	discriminant;
	float	sqrt_disc;

	discriminant = t.y * t.y - 4 * t.x * t.z;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	*t1 = (-t.y - sqrt_disc) / (2 * t.x);
	*t2 = (-t.y + sqrt_disc) / (2 * t.x);
	return (1);
}
