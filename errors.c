#include "so_long.h"

static int	horizontalwall(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->width)
	{
		if (vars->map[0][i] != '1' || vars->map[vars->height - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	verticalwall(t_vars *vars)
{
	int	height;

	height = 0;
	while (height < vars->height)
	{
		if ((vars->map[height][0] != '1' || vars->map[height][vars->width - 1] != '1'))
			return (0);
		height++;
	}
	return (1);
}

static void	if_walls(t_vars *vars)
{
	int	verticalwalls;
	int	horizontalwalls;

	verticalwalls = verticalwall(vars);
	horizontalwalls = horizontalwall(vars);
	if (!verticalwalls || !horizontalwalls)
	{
		printf("This map is missing the walls\n");
		exit_game(vars);
	}
}

static void	count_checker(t_vars *vars, int height, int width)
{
	if (vars->map[height][width] != '1' &&
		vars->map[height][width] != '0' &&
		vars->map[height][width] != 'P' &&
		vars->map[height][width] != 'E' &&
		vars->map[height][width] != 'C' &&
		vars->map[height][width] != '\n')
	{
		printf("\nError Here! %c\n", vars->map[height][width]);
		exit_game(vars);
	}
	if (vars->map[height][width] == 'C')
			vars->collectible_count++;
	if (vars->map[height][width] == 'P')
			vars->player_count++;
	if (vars->map[height][width] == 'E')
			vars->exit_count++;
}

void check_counts(t_vars *vars)
{
    if (vars->player_count == 0)
        printf("Player is missing!\n");
    if (vars->collectible_count < 1)
        printf("No collectibles found!\n");
    if (vars->exit_count != 1)
        printf("Exit is missing or invalid!\n");
}

void character_valid(t_vars *vars)
{
    int height = 0, width;

    vars->player_count = 0;
    vars->collectible_count = 0;
    vars->exit_count = 0;
    
    while (height < vars->height - 1)
    {
        width = 0;
        while (width <= vars->width)
        {
            count_checker(vars, height, width);
            width++;
        }
        height++;
    }
    
    if (vars->player_count != 1 || vars->collectible_count < 1 || vars->exit_count != 1)
    {
        printf("Error: Something is wrong!\n");
        check_counts(vars);
        exit_game(vars);
    }
}


void	check_errors(t_vars *vars)
{
	if_walls(vars);
	character_valid(vars);
}
