/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:31:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/17 22:03:37 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

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


int main(void)
{
    t_minirt	minirt;
    t_scene		scene;

    win_init(&minirt);
	scene = parse_elements("render.rt");
	if (!scene.camera || !scene.ambient) {
	    fprintf(stderr, "Invalid scene setup.\n");
	    return (1);
	}

	minirt.scene = &scene;
	print_scene(minirt.scene);

	render_scene(scene, minirt.mlx);
    mlx_put_image_to_window(minirt.mlx->mlx, minirt.mlx->mlx_win, minirt.mlx->img, 0, 0);
    mlx_loop(minirt.mlx->mlx);

    free(scene.spheres);
    free(scene.planes);
    free(scene.cylinders);
    free(scene.lights);
    
    return 0;
}