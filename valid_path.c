#include "so_long.h"

void	free_arr(char **arr, int height)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < height && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_temp_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}


char	**copy_map(char **map, int height)
{
	char		**temp;
	int			i;

	if (!map || height <= 0)
		return (NULL);
	temp = (char **)malloc(sizeof(char *) * (height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < height)
	{
		temp[i] = strdup(map[i]);
		if (!temp[i])
		{
			free_arr(temp, i);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

void flood_fill_map(char **map, int y, int x, t_vars *vars)
{
    if (y < 0 || x < 0 || y >= vars->height || x >= vars->width || map[y][x] == '1' || map[y][x] == 'V')
        return;

    if (map[y][x] == 'C')
        vars->collectible_count--;
    else if (map[y][x] == 'E')
        vars->check_exit = 1;

    map[y][x] = 'V'; // Mark as visited

    flood_fill_map(map, y - 1, x, vars); // Up
    flood_fill_map(map, y + 1, x, vars); // Down
    flood_fill_map(map, y, x - 1, vars); // Left
    flood_fill_map(map, y, x + 1, vars); // Right
}

int	check_flood_fill(char **map, t_vars *vars)
{
	if (!map || !vars || vars->collectible_count != 0 || vars->exit_count != 1)
	{
		printf("ERROR: Path is blocked. Collectibles or exit are unreachable.\n");
		free_temp_map(map);
		return (-1);
	}
	free_temp_map(map); 
	return (1);
}

int check_valid_path(t_vars *vars)
{
    char **temp;
    int result;

    if (!vars || !vars->map)
        return (0);
    temp = copy_map(vars->map, vars->height);
    if (!temp)
        return (0);
    vars->check_exit = 0;
    // Find player position
    for (int y = 0; y < vars->height; y++)
    {
        for (int x = 0; x < vars->width; x++)
        {
            if (temp[y][x] == 'P')
            {
                flood_fill_map(temp, y, x, vars);
                break;
            }
        }
    }
    result = (vars->collectible_count == 0 && vars->check_exit == 1);
    free_temp_map(temp);
    return (result);
}





