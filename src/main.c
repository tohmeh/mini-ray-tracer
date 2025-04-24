/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:31:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/24 19:27:02 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

#define MAIN_RENDER_OFFSET CONTROL_PANEL_WIDTH

t_vector new_vector(float x, float y, float z)
{
    t_vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

void print_vector(const char *name, t_vector v) {
    printf("%s: (%.2f, %.2f, %.2f)\n", name, v.x, v.y, v.z);
}

void print_color(const char *name, t_color c) {
    printf("%s: (R: %d, G: %d, B: %d)\n", name, c.r, c.g, c.b);
}

void print_scene(t_scene *scene) {
    if (scene->ambient) {
        printf("== Ambient Light ==\n");
        printf("Ratio: %.2f\n", scene->ambient->ratio);
        print_color("Color", scene->ambient->color);
    }

    if (scene->camera) {
        printf("\n== Camera ==\n");
        print_vector("Position", scene->camera->position);
        print_vector("Direction", scene->camera->direction);
        printf("FOV: %.2f\n", scene->camera->fov);
    }

    t_light *light = scene->lights;
    int light_index = 1;
    while (light) {
        printf("\n== Light %d ==\n", light_index++);
        print_vector("Position", light->position);
        printf("Brightness: %.2f\n", light->brightness);
        print_color("Color", light->color);
        light = light->next;
    }

    t_sphere *sphere = scene->spheres;
    int sphere_index = 1;
    while (sphere) {
        printf("\n== Sphere %d ==\n", sphere_index++);
        print_vector("Center", sphere->center);
        printf("Radius: %.2f\n", sphere->radius);
        print_color("Color", sphere->color);
        sphere = sphere->next;
    }

    t_plane *plane = scene->planes;
    int plane_index = 1;
    while (plane) {
        printf("\n== Plane %d ==\n", plane_index++);
        print_vector("Point", plane->point);
        print_vector("Normal", plane->normal);
        print_color("Color", plane->color);
        plane = plane->next;
    }

    t_cylinder *cylinder = scene->cylinders;
    int cyl_index = 1;
    while (cylinder) {
        printf("\n== Cylinder %d ==\n", cyl_index++);
        print_vector("Center", cylinder->center);
        print_vector("Axis", cylinder->axis);
        printf("Diameter: %.2f\n", cylinder->diameter);
        printf("Height: %.2f\n", cylinder->height);
        print_color("Color", cylinder->color);
        cylinder = cylinder->next;
    }
}

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



int main(int argc, char **argv)
{
    t_minirt	minirt;
    t_scene		scene;
    

	if (argc == 2 && )
	{
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
    
}