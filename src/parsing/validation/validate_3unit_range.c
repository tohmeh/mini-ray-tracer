/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_3unit_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:47:10 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:58:56 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_3unit_range(char **str, float min, float max)
{
	if (ft_validate_range(ft_atof(str[0]), min, max)
		&& ft_validate_range(ft_atof(str[1]), min, max)
		&& ft_validate_range(ft_atof(str[0]), min, max))
		return (1);
	return (0);
}
