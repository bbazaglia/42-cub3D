#include "cub3d.h"

void	put_valid_pixel(mlx_image_t *mlx_image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(mlx_image, x, y, color);
}

void	render_map(t_game *game)
{
	size_t i;
	size_t j;
	t_coord point_1;
	t_coord point_2;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			point_1.x = CELL * j;
			point_1.y = CELL * i;
			point_2.x = (CELL * j) + (CELL - 1);
			point_2.y = (CELL * i) + (CELL - 1);
			if (game->map[i][j] == '1')
            {
				point_1.color = 0xffffffff;
				point_2.color = 0xffffffff;
            }
			else
            {
				point_1.color = 0x00000000;
				point_2.color = 0x00000000;
            }
			fill_cell(&point_1, &point_2, game->mlx_image);
            j++;
		}
        i++;
	}
}

void fill_cell(t_coord *point_1, t_coord *point_2, mlx_image_t *mlx_image)
{
    int x;
    int y;
    uint32_t	color;

    x = point_1->x;
    y = point_1->y;
    color = point_1->color;

    while(y <= point_2->y)
    {
        x = point_1->x;
        while(x <= point_2->x)
        {
		    put_valid_pixel(mlx_image, x, y, color);
            x++;
        }
        y++;
    }
}