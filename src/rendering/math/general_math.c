/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:42:43 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/29 16:33:16 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector subtract_vectors(t_vector v1, t_vector v2) {
    t_vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

t_vector multiply_vector_by_scalar(t_vector v, float scalar) {
    t_vector result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}

float dot_product(t_vector v1, t_vector v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
t_vector cross_product(t_vector v1, t_vector v2)
{
    t_vector result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}
t_vector add_vectors(t_vector v1, t_vector v2)
{
    t_vector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}
float	vector_length(t_vector A)
{
	return sqrtf(powf(A.x, 2) + powf(A.y, 2) + powf(A.z , 2));
}

t_vector normalize_vector(t_vector v)
{
    float length = vector_length(v);
    if (length > 0)
        return (t_vector){v.x / length, v.y / length, v.z / length};
    return (t_vector){0, 0, 0}; // Return zero vector if input is zero
}
