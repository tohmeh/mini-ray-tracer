/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:26:14 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:59:06 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static float	handle_integer_part(const char *str, int *i)
{
	float	n;

	n = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (n);
}

static float	handle_decimal_part(const char *str, int *i)
{
	float	decimal;
	int		decimal_places;

	decimal = 0;
	decimal_places = 0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			decimal = decimal * 10 + (str[*i] - '0');
			decimal_places++;
			(*i)++;
		}
	}
	while (decimal_places > 0)
	{
		decimal /= 10;
		decimal_places--;
	}
	return (decimal);
}

float	ft_atof(const char *str)
{
	int		i;
	float	n;
	float	decimal;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	n = handle_integer_part(str, &i);
	decimal = handle_decimal_part(str, &i);
	return ((n + decimal) * sign);
}
