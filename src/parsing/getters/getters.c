/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:21:35 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/26 19:42:55 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_color	get_color(char *str)
{
	t_color	color;
	char	**color_parts;

	color_parts = ft_split(str, ',');
	color = init_color(get_int(color_parts[0]), get_int(color_parts[1]),
			get_int(color_parts[2]));
	free_split(color_parts);
	return (color);
}

float	get_float(char *str)
{
	return (ft_atof(str));
}

int	get_int(char *str)
{
	return (ft_atoi(str));
}

t_vector	get_vector(char *str)
{
	t_vector	vector;
	char		**vector_parts;

	vector_parts = ft_split(str, ',');
	vector = init_vector(get_float(vector_parts[0]), get_float(vector_parts[1]),
			get_float(vector_parts[2]));
	free_split(vector_parts);
	return (vector);
}
