#include "fdf.h"

static void	translate(t_map *m, int key)
{
	if (key == KEY_UP)
		m->translate_y += 25;
	else if (key == KEY_LEFT)
		m->translate_x += 25;
	else if (key == KEY_DOWN)
		m->translate_y -= 25;
	else if (key == KEY_RIGHT)
		m->translate_x -= 25;
}

static void	rotate(t_map *m, int key)
{
	if (key == KEY_ROTATE_X_POS)
		m->angle_x += M_PI / 36;
	else if (key == KEY_ROTATE_X_NEG)
		m->angle_x -= M_PI / 36;
	else if (key == KEY_ROTATE_Y_POS)
		m->angle_y += M_PI / 36;
	else if (key == KEY_ROTATE_Y_NEG)
		m->angle_y -= M_PI / 36;
	else if (key == KEY_ROTATE_Z_POS)
		m->angle_z += M_PI / 36;
	else if (key == KEY_ROTATE_Z_NEG)
		m->angle_z -= M_PI / 36;
}

static void	zoom(t_map *m, int key)
{
	if (key == KEY_ZOOM_POS)
		m->zoom -= 0.1;
	else if (key == KEY_ZOOM_NEG)
		m->zoom += 0.1;
	if (m->zoom <= 0.1)
		m->zoom = 0.1;
	else if (m->zoom >= 10)
		m->zoom = 10;
}

static void	amplify(t_map *m, int key)
{
	const int	max = 100;

	if (key == KEY_ZVAL_POS)
		m->z_val -= 1;
	else if (key == KEY_ZVAL_NEG)
		m->z_val += 1;
	if (m->z_val >= max)
		m->z_val = max;
	else if (m->z_val <= -max)
		m->z_val = -max;
}

int	handle_key(int key, t_map *m)
{
	if (key == KEY_ESC)
		handle_error(m);
	else if (key == KEY_PROJECTION)
		set_projection(m);
	else if (key == KEY_UP || key == KEY_DOWN
		|| key == KEY_LEFT || key == KEY_RIGHT)
		translate(m, key);
	else if (key == KEY_ROTATE_X_POS || key == KEY_ROTATE_X_NEG
		|| key == KEY_ROTATE_Y_POS || key == KEY_ROTATE_Y_NEG
		|| key == KEY_ROTATE_Z_POS || key == KEY_ROTATE_Z_NEG)
		rotate(m, key);
	else if (key == KEY_ZOOM_POS || key == KEY_ZOOM_NEG)
		zoom(m, key);
	else if (key == KEY_ZVAL_POS || key == KEY_ZVAL_NEG)
		amplify(m, key);
	render_frame(m);
	return (0);
}
