/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:08:40 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 21:45:46 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

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

static void	calculate_light_contribution(t_light *light, t_hit_info hit,
		t_camera *camera, t_light_contrib *contrib)
{
	float	diffuse;
	float	specular;
	float	light_distance;
	float	attenuation;
	int		spec_intensity;

	diffuse = compute_diffuse_light(hit.normal, light->position, hit.point);
	specular = compute_specular_light(hit.normal, light->position, hit.point,
			camera->position, 16.0f);
	light_distance = vector_length(subtract_vectors(light->position,
				hit.point));
	attenuation = 1.0 / (1.0 + 0.01 * light_distance + 0.001 * light_distance
			* light_distance);
	contrib->diffuse_r = (int)(hit.color.r * diffuse * light->brightness
			* attenuation);
	contrib->diffuse_g = (int)(hit.color.g * diffuse * light->brightness
			* attenuation);
	contrib->diffuse_b = (int)(hit.color.b * diffuse * light->brightness
			* attenuation);
	spec_intensity = (int)(240.0f * specular * light->brightness * attenuation);
	contrib->final_r += contrib->diffuse_r + spec_intensity;
	contrib->final_g += contrib->diffuse_g + spec_intensity;
	contrib->final_b += contrib->diffuse_b + spec_intensity;
}

static int	apply_lighting(t_scene scene, t_hit_info hit)
{
	t_light_contrib	contrib;
	t_light			*light;

	calculate_ambient_light(scene.ambient, hit.color, &contrib);
	light = scene.lights;
	if (light && !in_shadow(hit.point, light, scene))
		calculate_light_contribution(light, hit, scene.camera, &contrib);
	if (contrib.final_r > 255)
		contrib.final_r = 255;
	if (contrib.final_g > 255)
		contrib.final_g = 255;
	if (contrib.final_b > 255)
		contrib.final_b = 255;
	return ((contrib.final_r << 16) | (contrib.final_g << 8) | contrib.final_b);
}

void	process_pixel(t_scene scene, t_mlx *mlx, int i, int j)
{
	t_ray		ray;
	int			pixel_color;
	float		closest_t;
	t_hit_info	hit;

	ray = generate_ray(scene.camera, i, j);
	pixel_color = 0xAAAAAA;
	if (find_closest_intersection(ray, scene, &closest_t, &hit))
		pixel_color = apply_lighting(scene, hit);
	put_pixel(mlx, i, j, pixel_color);
}

void	render_scene(t_scene scene, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			process_pixel(scene, mlx, i, j);
			j++;
		}
		i++;
	}
}
