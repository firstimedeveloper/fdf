#include "fdf.h"

void	handle_error(t_map *m)
{
	free(m->map);
	exit(0);
}
