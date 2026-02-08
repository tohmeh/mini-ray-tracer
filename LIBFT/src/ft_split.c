/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:16:26 by mtohmeh           #+#    #+#             */
/*   Updated: 2024/08/12 10:56:26 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/LIBFT.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	count_words(const char *str, const char *delimiters)
{
	int	i;
	int	count;
	int	inword;

	inword = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (inword == 0 && ft_strchr(delimiters, str[i]) == NULL)
		{
			inword = 1;
			count++;
		}
		else if (ft_strchr(delimiters, str[i]) != NULL)
			inword = 0;
		i++;
	}
	return (count);
}

void	iterate(const char *s, const char *delimit, char **result, char *buffer)
{
	int	i;
	int	j;
	int	buffer_count;

	buffer_count = 0;
	i = -1;
	j = 0;
	while (++i <= (int)strlen(s))
	{
		if (ft_strchr(delimit, s[i]) == NULL && s[i] != '\0')
			buffer[buffer_count++] = s[i];
		else
		{
			if (buffer_count > 0)
			{
				result[j] = malloc((buffer_count + 1) * sizeof(char));
				buffer[buffer_count] = '\0';
				ft_strlcpy(result[j++], buffer, buffer_count + 1);
				buffer_count = 0;
			}
		}
	}
	result[j] = NULL;
}

char	**ft_split(const char *s, const char *delimiters)
{
	char	**result;
	char	buffer[1000];

	result = malloc(sizeof(char *) * (count_words(s, delimiters) + 1));
	iterate(s, delimiters, result, buffer);
	return (result);
}
