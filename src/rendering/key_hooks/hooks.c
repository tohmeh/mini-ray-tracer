/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:45:03 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 21:48:40 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define KEY_T 116
#define KEY_F 102
#define KEY_G 103
#define KEY_H 104
#define KEY_R 114
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108

typedef enum e_directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}				t_directions;

typedef enum AXIS
{
	X,
	Y,
	Z
}	AXIS;

int	close_window(t_minirt *minirt_struct)
{
	mlx_destroy_window(minirt_struct->mlx->mlx, minirt_struct->mlx->mlx_win);
	exit(0);
	return (0);
}

static t_vector	get_translation_delta(t_directions direction, float move_step)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	delta.z = 0;
	if (direction == UP)
		delta.z = move_step;
	else if (direction == DOWN)
		delta.z = -move_step;
	else if (direction == LEFT)
		delta.x = -move_step;
	else if (direction == RIGHT)
		delta.x = move_step;
	return (delta);
}

static void	translate_sphere(t_sphere *s, t_vector delta)
{
	s->center = add_vectors(s->center, delta);
}

static void	translate_cylinder(t_cylinder *c, t_vector delta)
{
	c->center = add_vectors(c->center, delta);
}

static void	translate_plane(t_plane *p, t_vector delta)
{
	p->point = add_vectors(p->point, delta);
}

int	translate_object(t_minirt *minirt, t_directions direction)
{
	t_scene		*scene;
	t_vector	delta;
	float		move_step;

	scene = minirt->scene;
	move_step = 0.2f;
	if (!scene->object_hit)
		return (0);
	delta = get_translation_delta(direction, move_step);
	if (scene->object_hit->type == SPHERE)
		translate_sphere((t_sphere *)scene->object_hit->obj, delta);
	else if (scene->object_hit->type == CYLINDER)
		translate_cylinder((t_cylinder *)scene->object_hit->obj, delta);
	else if (scene->object_hit->type == PLANE)
		translate_plane((t_plane *)scene->object_hit->obj, delta);
	return (1);
}
t_vector rotate_vector_z(t_vector v, float angle)
{
	t_vector result;
	result.x = v.x * cos(angle) - v.y * sin(angle);
	result.y = v.x * sin(angle) + v.y * cos(angle);
	result.z = v.z; // Z stays the same
	return result;
}
t_vector rotate_vector_x(t_vector v, float angle)
{
	t_vector result;
	result.x = v.x; // X stays the same
	result.y = v.y * cos(angle) - v.z * sin(angle);
	result.z = v.y * sin(angle) + v.z * cos(angle);
	return result;
}
t_vector rotate_vector_y(t_vector v, float angle)
{
	t_vector result;

	result.x = v.x * cos(angle) + v.z * sin(angle);
	result.y = v.y;
	result.z = -v.x * sin(angle) + v.z * cos(angle);
	return (result);
}


int rotate_object(t_minirt *minirt, AXIS AXE)
{
    t_scene *scene = minirt->scene;
    float angle = 0.1f; // Rotation angle in radians

    if (!scene->object_hit)
        return (0);

    if (AXE == X)
    {
        if (scene->object_hit->type == CYLINDER)
        {
            t_cylinder *obj = (t_cylinder *)scene->object_hit->obj;
            obj->axis = rotate_vector_x(obj->axis, angle);
            obj->axis = normalize_vector(obj->axis);
        }
        else if (scene->object_hit->type == PLANE)
        {
            t_plane *obj = (t_plane *)scene->object_hit->obj;
            obj->normal = rotate_vector_x(obj->normal, angle);
            obj->normal = normalize_vector(obj->normal);
        }
    }
    else if (AXE == Y)
    {
        if (scene->object_hit->type == CYLINDER)
        {
            t_cylinder *obj = (t_cylinder *)scene->object_hit->obj;
            obj->axis = rotate_vector_y(obj->axis, angle);
            obj->axis = normalize_vector(obj->axis);
        }
        else if (scene->object_hit->type == PLANE)
        {
            t_plane *obj = (t_plane *)scene->object_hit->obj;
            obj->normal = rotate_vector_y(obj->normal, angle);
            obj->normal = normalize_vector(obj->normal);
        }
    }
    else if (AXE == Z)
    {
        if (scene->object_hit->type == CYLINDER)
        {
            t_cylinder *obj = (t_cylinder *)scene->object_hit->obj;
            obj->axis = rotate_vector_z(obj->axis, angle);
            obj->axis = normalize_vector(obj->axis);
        }
        else if (scene->object_hit->type == PLANE)
        {
            t_plane *obj = (t_plane *)scene->object_hit->obj;
            obj->normal = rotate_vector_z(obj->normal, angle);
            obj->normal = normalize_vector(obj->normal);
        }
    }

    return (1);
}


int	mouse_handler(int button, int x, int y, void *param)
{
	t_minirt	*minirt;
	t_scene		*scene;
	object_info	hit;
	float		delta;
	t_sphere	*s;
	t_cylinder	*c;

	if (x >= CONTROL_PANEL_WIDTH)
	{
		x = x - CONTROL_PANEL_WIDTH;
		minirt = (t_minirt *)param;
		scene = minirt->scene;
		if (button == 1)
		{
			hit = object_detector(x, y, scene);
			// Free previous allocation if it exists
			if (scene->object_hit)
				free(scene->object_hit);
			scene->object_hit = malloc(sizeof(object_info));
			scene->object_hit->intersection_point = hit.intersection_point;
			scene->object_hit->normal = hit.normal;
			scene->object_hit->obj = hit.obj;
			scene->object_hit->type = hit.type;
		}
		if (button == 4 || button == 5)
		{
			if (scene->object_hit)
			{
				delta = (button == 4) ? 0.1f : -0.1f;
				if (scene->object_hit->type == SPHERE)
				{
					s = (t_sphere *)scene->object_hit->obj;
					s->radius += delta;
					if (s->radius < 0.1f)
						s->radius = 0.1f;
					fflush(stdout);
				}
				else if (scene->object_hit->type == CYLINDER)
				{
					c = (t_cylinder *)scene->object_hit->obj;
					c->diameter += delta;
					c->height += delta;
					if (c->diameter < 0.1f)
						c->diameter = 0.1f;
					if (c->height < 0.1f)
						c->height = 0.1f;
				}
				// Render the scene with the updated object
				render_scene(*scene, minirt->mlx);
				mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win,
					minirt->mlx->img, CONTROL_PANEL_WIDTH, 0);
			}
		}
	}
	
	return (0);
}

static void	handle_exit_key(int key, t_minirt *rt)
{
	if (key == KEY_ESC)
		close_window(rt);
}

static void	handle_movement_key(int key, t_camera *cam, float speed)
{
	t_vector	right;

	if (key == KEY_W)
		move_camera(cam, cam->direction, speed);
	else if (key == KEY_S)
		move_camera(cam, multiply_vector_by_scalar(cam->direction, -1), speed);
	else if (key == KEY_A || key == KEY_D)
	{
		right = compute_right_vector(cam->direction);
		if (key == KEY_A)
			move_camera(cam, multiply_vector_by_scalar(right, -1), speed);
		else
			move_camera(cam, right, speed);
	}
}

static void	handle_camera_rotation_key(int key, t_camera *cam, float speed)
{
	if (key == KEY_LEFT)
		rotate_camera_y(cam, speed);
	else if (key == KEY_RIGHT)
		rotate_camera_y(cam, -speed);
	else if (key == KEY_UP)
		rotate_camera_x(cam, -speed);
	else if (key == KEY_DOWN)
		rotate_camera_x(cam, speed);
}

static void	handle_translation_key(int key, t_minirt *rt)
{
	if (key == KEY_T)
		translate_object(rt, UP);
	else if (key == KEY_G)
		translate_object(rt, DOWN);
	else if (key == KEY_F)
		translate_object(rt, LEFT);
	else if (key == KEY_H)
		translate_object(rt, RIGHT);
}
void	handle_object_rotation_key(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_J)
		rotate_object(minirt, X);
	else if (keycode == KEY_K)
		rotate_object(minirt, Y);
	else if (keycode == KEY_L)
		rotate_object(minirt, Z);
}
int	key_hook(int keycode, t_minirt *rt)
{
	const float	move_speed = 0.5f;
	const float	rotation_speed = 0.05f;
	t_camera	*cam;

	if (!rt || !rt->scene)
	{
		printf("Error: miniRT struct or scene not initialized\n");
		return (0);
	}
	cam = rt->scene->camera;
	handle_exit_key(keycode, rt);
	handle_movement_key(keycode, cam, move_speed);
	handle_camera_rotation_key(keycode, cam, rotation_speed);
	handle_object_rotation_key(keycode, rt);
	handle_translation_key(keycode, rt);
	render_scene(*rt->scene, rt->mlx);
	mlx_put_image_to_window(rt->mlx->mlx, rt->mlx->mlx_win, rt->mlx->img, CONTROL_PANEL_WIDTH, 0);
	return (0);
}