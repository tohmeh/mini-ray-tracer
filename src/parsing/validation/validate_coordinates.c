/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:23:08 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/26 19:45:25 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_coordinates(char *str)
{
	char	**parts;

	parts = ft_split(str, ",");
	if (parts_size(parts) != 3)
		return (0);
	if (ft_is_number(parts[0]) && ft_is_number(parts[1])
		&& ft_is_number(parts[2]))
	{
		free_split(parts);
		return (1);
	}
	free_split(parts);
	return (0);
}
