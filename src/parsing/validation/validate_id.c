/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:32:23 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:58:46 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_id(char *str, const char *comp, int size)
{
	if (ft_strncmp(str, comp, 0) == 0 && ft_strlen(str) == size)
		return (1);
	return (0);
}
