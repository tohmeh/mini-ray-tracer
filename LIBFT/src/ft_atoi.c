/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:53:00 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 14:40:26 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/../include/LIBFT.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	check_overflow(long result, int digit, int sign)
{
	if (sign == 1 && result > (INT_MAX - digit) / 10)
		ft_error("Integer overflow");
	if (sign == -1 && (-result) < (INT_MIN + digit) / 10)
		ft_error("Integer underflow");
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;
	int		digit;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		check_overflow(result, digit, sign);
		result = result * 10 + digit;
		i++;
	}
	return ((int)(result * sign));
}