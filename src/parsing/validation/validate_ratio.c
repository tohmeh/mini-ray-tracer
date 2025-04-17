/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:20:21 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 15:52:39 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_ratio(char *str)
{
	float	ratio;

	if (!ft_is_float(str))
	{
		return (0);		
	}
	ratio = ft_atof(str);
	if (!ft_validate_range(ratio, 0.0, 1.0))
	{
		return (0);		
	}
	return (1);
}
