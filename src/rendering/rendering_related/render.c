/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:08:40 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:44:27 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"
#include <omp.h>

static void	calculate_ambient_light(t_ambient *ambient, t_color obj_color,
		t_light_contrib *contrib)
{
	float	ambient_factor;

	ambient_factor = ambient->ratio;
	contrib->ambient_r = (int)(obj_color.r * ambient_factor);
	contrib->ambient_g = (int)(obj_color.g * ambient_factor);
	contrib->ambient_b = (int)(obj_color.b * ambient_factor);
	contrib->final_r = contrib->ambient_r;
	contrib->final_g = contrib->ambient_g;
	contrib->final_b = contrib->ambient_b;
}

static float	compute_fresnel(t_vector normal, t_vector view_dir)
{
	float	fresnel;
	float	cos_theta;

	cos_theta = fabs(dot_product(normal, view_dir));
	fresnel = powf(1.0f - cos_theta, 3.0f);
	return (fresnel * 0.05f);
}

static void	calculate_light_contribution(t_light *light, t_hit_info hit,
		t_camera *camera, t_light_contrib *contrib)
{
	float	diffuse;
	float	specular;
	float	light_distance;
	float	attenuation;
	float	fresnel;
	t_vector view_dir;

	diffuse = compute_diffuse_light(hit.normal, light->position, hit.point);
	specular = compute_specular_light(hit.normal, light->position, hit.point,
			camera->position);
	light_distance = vector_length(subtract_vectors(light->position, hit.point));
	attenuation = 1.0 / (1.0 + 0.03 * light_distance + 0.005 * light_distance
			* light_distance);
	view_dir = normalize_vector(subtract_vectors(camera->position, hit.point));
	fresnel = compute_fresnel(hit.normal, view_dir);
	contrib->diffuse_r += (int)(hit.color.r * (diffuse * 0.45f + fresnel) * light->brightness * attenuation);
	contrib->diffuse_g += (int)(hit.color.g * (diffuse * 0.45f + fresnel) * light->brightness * attenuation);
	contrib->diffuse_b += (int)(hit.color.b * (diffuse * 0.45f + fresnel) * light->brightness * attenuation);
	contrib->final_r += (int)(100.0f * specular * light->brightness * attenuation);
	contrib->final_g += (int)(100.0f * specular * light->brightness * attenuation);
	contrib->final_b += (int)(100.0f * specular * light->brightness * attenuation);
}

static int	apply_lighting(t_scene scene, t_hit_info hit)
{
	t_light_contrib	contrib;
	t_light			*light;

	calculate_ambient_light(scene.ambient, hit.color, &contrib);
	contrib.diffuse_r = 0;
	contrib.diffuse_g = 0;
	contrib.diffuse_b = 0;
	light = scene.lights;
	while (light)
	{
		if (!in_shadow(hit.point, light, scene))
			calculate_light_contribution(light, hit, scene.camera, &contrib);
		light = light->next;
	}
	contrib.final_r += contrib.diffuse_r;
	contrib.final_g += contrib.diffuse_g;
	contrib.final_b += contrib.diffuse_b;
	if (contrib.final_r > 255)
		contrib.final_r = 255;
	if (contrib.final_g > 255)
		contrib.final_g = 255;
	if (contrib.final_b > 255)
		contrib.final_b = 255;
	return ((contrib.final_r << 16) | (contrib.final_g << 8) | contrib.final_b);
}

static int	get_background_color(int j)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = (float)j / (float)HEIGHT;
	r = (int)((1.0f - t) * 135 + t * 35);
	g = (int)((1.0f - t) * 206 + t * 80);
	b = (int)((1.0f - t) * 235 + t * 130);
	return ((r << 16) | (g << 8) | b);
}

void	process_pixel(t_scene scene, t_mlx *mlx, int i, int j)
{
	t_ray		ray;
	int			pixel_color;
	float		closest_t;
	t_hit_info	hit;

	ray = generate_ray(scene.camera, i, j);
	pixel_color = get_background_color(j);
	if (find_closest_intersection(ray, scene, &closest_t, &hit))
		pixel_color = apply_lighting(scene, hit);
	put_pixel(mlx, i, j, pixel_color);
}

void	render_scene(t_scene scene, t_mlx *mlx)
{
	int	i;
	int	j;

	#pragma omp parallel for private(j) schedule(dynamic, 16)
	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			process_pixel(scene, mlx, i, j);
		}
	}
}
