/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_hfield.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:40:57 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 13:36:48 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_hfield(char *str)
{
	float	field;

	field = get_float(str);
	if (!ft_validate_range(field, 0, 180))
		return (0);
	return (1);
}
