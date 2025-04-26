/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:31:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 13:53:25 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void draw_control_panel(t_mlx *mlx)
{
    int text_color;
    text_color = 0xFFFFFF;
    // // Write control instructions
    int y_pos = 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "CONTROLS:");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "Camera Movement:");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "W - Move forward");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "S - Move backward");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "A - Move left");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "D - Move right");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "Camera Rotation:");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "UP - Look up");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "DOWN - Look down");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "LEFT - Look left");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "RIGHT - Look right");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "Object Selection:");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "Left Click - Select");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "Scroll - Resize");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "Object Translation:");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "T - Move forward");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "G - Move backward");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "F - Move left");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "H - Move right");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "Object Rotation:");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "J - Rotate X axis");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "K - Rotate Y axis");
    y_pos += 20;
    mlx_string_put(mlx->mlx, mlx->mlx_win, 30, y_pos, text_color, "L - Rotate Z axis");
    y_pos += 30;
    
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "ESC - Exit");
	
}



int main(void)
{
    t_minirt	minirt;
    t_scene		scene;
    

		// Adjust window size to accommodate control panel
	int total_width = WIDTH + CONTROL_PANEL_WIDTH;

	// Initialize window with new width
	win_init(&minirt, total_width);
	
	scene = parse_elements("render.rt");
	if (!scene.camera || !scene.ambient) {
		fprintf(stderr, "Invalid scene setup.\n");
		return (1);
	}
	
	minirt.scene = &scene;
	// Initialize object_hit to NULL
	scene.object_hit = NULL;
	
	// Initial render
	mlx_put_image_to_window(minirt.mlx->mlx, minirt.mlx->mlx_win, minirt.mlx->img, CONTROL_PANEL_WIDTH, 0);

	draw_control_panel(minirt.mlx);
	render_scene(scene, minirt.mlx);
	
	mlx_mouse_hook(minirt.mlx->mlx_win, mouse_handler, &minirt);
	mlx_key_hook(minirt.mlx->mlx_win, key_hook, &minirt);
	mlx_hook(minirt.mlx->mlx_win, 17, 0, close_window, &minirt); 
	
	mlx_loop(minirt.mlx->mlx);
	
	// Free resources
	if (scene.object_hit)
		free(scene.object_hit);
	free(scene.spheres);
	free(scene.planes);
	free(scene.cylinders);
	free(scene.lights);
	
	return 0;	    
}