/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:14:30 by gakhoury          #+#    #+#             */
/*   Updated: 2025/06/28 15:39:10 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	count_words(const char *str)
{
	int	i;
	int	count;
	int	inword;

	inword = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (inword == 0 && !is_delimiter(str[i]))
		{
			inword = 1;
			count++;
		}
		else if (is_delimiter(str[i]))
			inword = 0;
		i++;
	}
	return (count);
}

static void	iterate(const char *s, char **result, char *buffer)
{
	int	i;
	int	j;
	int	buffer_count;

	buffer_count = 0;
	i = -1;
	j = 0;
	while (++i <= ft_strlen((char *)s))
	{
		if (s[i] != '\0' && !is_delimiter(s[i]))
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



char	**ft_split_by_ws(const char *s)
{
	char	**result;
	char	buffer[1000];

	result = malloc(sizeof(char *) * (count_words(s) + 1));
	iterate(s, result, buffer);
	return (result);
}

