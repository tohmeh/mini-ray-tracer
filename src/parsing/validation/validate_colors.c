/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:51:19 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/26 19:44:27 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_colors(char *str)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts_size(parts) != 3)
		return (0);
	if (ft_is_integer(parts[0]) && ft_is_integer(parts[1])
		&& ft_is_integer(parts[2]))
	{
		if (validate_3unit_range(parts, (float)0, (float)255))
		{
			free_split(parts);
			return (1);
		}
	}
	free_split(parts);
	return (0);
}
