/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:35:20 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:52:09 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	apply_ambient_light(t_scene scene, int *pixel_color)
{
	float	ambient_intensity;
	t_color	ambient_color;
	int		final_r;
	int		final_g;
	int		final_b;

	ambient_intensity = scene.ambient->ratio;
	ambient_color = scene.ambient->color;
	final_r = (((*pixel_color >> 16) & 0xFF) * ambient_intensity)
		+ (((ambient_color.r >> 16) & 0xFF) * (1 - ambient_intensity));
	final_g = (((*pixel_color >> 8) & 0xFF) * ambient_intensity)
		+ (((ambient_color.g >> 8) & 0xFF) * (1 - ambient_intensity));
	final_b = ((*pixel_color & 0xFF) * ambient_intensity)
		+ ((ambient_color.b & 0xFF) * (1 - ambient_intensity));
	if (final_r > 255)
		final_r = 255;
	if (final_g > 255)
		final_g = 255;
	if (final_b > 255)
		final_b = 255;
	*pixel_color = (final_r << 16) | (final_g << 8) | final_b;
}

float	compute_diffuse_light(t_vector normal, t_vector light_pos,
		t_vector intersection_point)
{
	t_vector	light_dir;
	float		intensity;

	light_dir = subtract_vectors(light_pos, intersection_point);
	light_dir = normalize_vector(light_dir);
	intensity = dot_product(normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	return (intensity);
}

float	compute_specular_light(t_vector normal, t_vector light_pos,
		t_vector intersection_point, t_vector camera_pos)
{
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	reflect_dir;
	float		spec;
	float		shininess;

	shininess = 64.0f;
	light_dir = normalize_vector(subtract_vectors(light_pos,
				intersection_point));
	view_dir = normalize_vector(subtract_vectors(camera_pos,
				intersection_point));
	reflect_dir = subtract_vectors(multiply_vector_by_scalar(normal, 2.0f
				* dot_product(normal, light_dir)), light_dir);
	spec = powf(fmax(dot_product(reflect_dir, view_dir), 0.0), shininess);
	return (spec);
}

int	in_shadow(t_vector intersection_point, t_light *light, t_scene scene)
{
	t_vector	light_dir;
	float		light_distance;
	t_ray		shadow_ray;

	light_dir = normalize_vector(subtract_vectors(light->position,
				intersection_point));
	light_distance = vector_length(subtract_vectors(light->position,
				intersection_point));
	shadow_ray = create_shadow_ray(intersection_point, light_dir);
	if (is_sphere_in_shadow(shadow_ray, light_distance, scene))
		return (1);
	if (is_plane_in_shadow(shadow_ray, light_distance, scene))
		return (1);
	if (is_cylinder_in_shadow(shadow_ray, light_distance, scene))
		return (1);
	return (0);
}
