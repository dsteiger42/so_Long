#include "so_long.h"

void put_player(t_vars *vars, int width, int height)
{
    mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, width * vars->img_width, height * vars->img_height);
    vars->player_x = width;
    vars->player_y = height;
}

void put_collectable(t_vars *vars, int width, int height)
{
    mlx_put_image_to_window(vars->mlx, vars->win, vars->collectible_img, width * vars->img_width, height * vars->img_height);
    vars->collectible_count++;
}

void put_exit(t_vars *vars, int width, int height)
{
   mlx_put_image_to_window(vars->mlx, vars->win, vars->exit_img, width * vars->img_width, height * vars->img_height);
}

void load_images(t_vars *vars)
{
    vars->player_img = mlx_xpm_file_to_image(vars->mlx, "images/player.xpm", &vars->img_width, &vars->img_height);
    vars->collectible_img = mlx_xpm_file_to_image(vars->mlx, "images/collectible.xpm", &vars->img_width, &vars->img_height);
    vars->exit_img = mlx_xpm_file_to_image(vars->mlx, "images/exit.xpm", &vars->img_width, &vars->img_height);
    vars->floor_img = mlx_xpm_file_to_image(vars->mlx, "images/floor.xpm", &vars->img_width, &vars->img_height);
    vars->wall_img = mlx_xpm_file_to_image(vars->mlx, "images/wall.xpm", &vars->img_width, &vars->img_height);

    if (!vars->player_img || !vars->collectible_img || !vars->exit_img || !vars->floor_img || !vars->wall_img)
    {
        printf("Error loading images.\n");
        exit_game(vars);
    }
}

void draw_map(t_vars *vars)
{
    int x;
    int y;

    vars->collectible_count = 0;
    y = 0;
    while (y < vars->height)
    {
        x = 0;
        while (x < vars->width)
        {
            if (vars->map[y][x] == '1')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_img, x * vars->img_width, y * vars->img_height);
            else if (vars->map[y][x] == '0')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->floor_img, x * vars->img_width, y * vars->img_height);
            else if (vars->map[y][x] == 'P')
                put_player(vars, x, y);
            else if (vars->map[y][x] == 'C')
                put_collectable(vars, x, y);
            else if (vars->map[y][x] == 'E')
                put_exit(vars, x, y);
            x++;
        }
        y++;
    }
}
static int	width_of_map(char *string)
{
	int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n')
		width--;
	return (width);
}

static int	add_line(t_vars *vars, char *line)
{
	char	**temporary;
	int		i;

	if (!line)
		return (0);
	i = 0;
	vars->height++;
	temporary = (char **)malloc(sizeof(char *) * (vars->height + 1));
	temporary[vars->height] = NULL;
	while (i < vars->height - 1)
	{
		temporary[i] = vars->map[i];
		i++;
	}
	temporary[i] = line;
	if (vars->map)
		free(vars->map);
	vars->map = temporary;
	return (1);
}

int map_reading(t_vars *vars)
{
    char *readmap;
    int x, y;

    vars->fd = open(vars->map_file, O_RDONLY);
    if (vars->fd < 0)
        return (0);
    vars->collectible_count = 0;
    while (1)
    {
        readmap = get_next_line(vars->fd);
        if (!add_line(vars, readmap))
            break;
    }
    close(vars->fd);
    vars->width = width_of_map(vars->map[0]);
    y = 0;
    while (y < vars->height)
    {
        x = 0;
        while (x < vars->width)
        {
            if (vars->map[y][x] == 'C')
                vars->collectible_count++;
            x++;
        }
        y++;
    }
    return (1);
}



