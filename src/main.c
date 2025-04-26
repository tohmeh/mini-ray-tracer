/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:31:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:45:02 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	is_rt_file(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	return (filename[len - 3] == '.' && filename[len - 2] == 'r'
		&& filename[len - 1] == 't');
}

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	if (argc == 2 && is_rt_file(argv[1]))
	{
		program_init(&minirt, argv[1]);
		draw_instruction_panel(minirt.mlx);
		setup_hooks(minirt);
		mlx_loop(minirt.mlx->mlx);
	}
	else
		printf("usage: ./miniRT filename.rt\n");
	return (0);
}
