#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include "minilibx/mlx.h"

# define BUFFER_SIZE 30
# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define KEY_ESC 53
# define KEY_UP 13
# define KEY_LEFT 0
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define KEY_ROTATE_X_POS 125
# define KEY_ROTATE_X_NEG 126
# define KEY_ROTATE_Y_POS 124
# define KEY_ROTATE_Y_NEG 123
# define KEY_ROTATE_Z_POS 14
# define KEY_ROTATE_Z_NEG 12
# define KEY_PROJECTION 15
# define KEY_ZOOM_POS 27
# define KEY_ZOOM_NEG 24
# define KEY_ZVAL_POS 43
# define KEY_ZVAL_NEG 47

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}	t_coord;

typedef struct s_map
{
	int		fd[2];

	int		is_iso;

	int		height;
	int		width;
	t_coord	*map;
	int		tile_length;

	int		z_val;

	int		camera_x_offset;
	int		camera_y_offset;

	int		translate_x;
	int		translate_y;

	double	angle_x;
	double	angle_y;
	double	angle_z;

	double	zoom;

	void	*mlx;
	void	*win;

	void	*img;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_map;

void	init_map(t_map *m);
void	set_coord(t_map *m);
void	handle_error(t_map *m);
int		handle_key(int key, t_map *m);
int		render_frame(t_map *m);
void	set_projection(t_map *m);
t_coord	project(t_map *m, t_coord coord);
void	draw(t_map *m);
void	rotate_x(int *y, int *z, double angle);
void	rotate_y(int *x, int *z, double angle);
void	rotate_z(int *x, int *y, double angle);
#endif
