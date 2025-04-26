/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_math2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:53:37 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:53:59 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float	vector_length(t_vector A)
{
	return (sqrtf(powf(A.x, 2) + powf(A.y, 2) + powf(A.z, 2)));
}

t_vector	normalize_vector(t_vector v)
{
	float	length;

	length = vector_length(v);
	if (length > 0)
		return ((t_vector){v.x / length, v.y / length, v.z / length});
	return ((t_vector){0, 0, 0});
}
