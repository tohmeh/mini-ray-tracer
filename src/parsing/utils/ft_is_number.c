/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:32:14 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/19 17:07:08 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_integer(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!is_digit(str[i]))
		return (0);
	while (str[i] != '\0')
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_float(const char *str)
{
	int	i;
	int	has_decimal_point;

	i = 0;
	has_decimal_point = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!is_digit(str[i]))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			if (has_decimal_point)
				return (0);
			has_decimal_point = 1;
		}
		else if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_number(const char *str)
{
	return (ft_is_integer(str) || ft_is_float(str));
}
