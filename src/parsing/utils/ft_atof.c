/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:26:14 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/19 17:28:07 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static double	handle_integer_part(const char *str, int *i)
{
	double	n;

	n = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (n);
}

static double	handle_decimal_part(const char *str, int *i)
{
	double	decimal;
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
	double	n;
	double	decimal;
	int		sign;
	double	result;

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
	result = (n + decimal) * sign;
	if (result > FLT_MAX || result < -FLT_MAX || isnan(result) || isinf(result))
		ft_error("Float overflow or underflow");
	return ((float)result);
}
