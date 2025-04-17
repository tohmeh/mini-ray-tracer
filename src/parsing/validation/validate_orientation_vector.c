/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_orientation_vector.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:42:50 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:19 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_orientation_vector(char *str)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts_size(parts) != 3)
		return (0);
	if (ft_is_number(parts[0]) && ft_is_number(parts[1])
		&& ft_is_number(parts[2]))
		if (validate_3unit_range(parts, -1, 1))
			return (1);
	return (0);
}
