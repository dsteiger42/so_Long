#include "so_long.h"

static int move_player(t_vars *vars, int new_x, int new_y)
{
    if (vars->map[new_y][new_x] == 'E')
    {
        if (vars->collectible_count != 0)
        {
            printf("You must collect all the items before exiting!\n");
            return (0);
        }
        printf("Congratulations! You've collected all the items and reached the exit!\n");
        exit_game(vars);
        return 1;
    }
    if (vars->map[new_y][new_x] == '0' || vars->map[new_y][new_x] == 'C')
    {
        if (vars->map[new_y][new_x] == 'C')
        {
            vars->collectible_count--;
            printf("Collectible picked up! Collectibles left: %d\n", vars->collectible_count);
        }
        vars->map[new_y][new_x] = 'P';
        vars->map[vars->player_y][vars->player_x] = '0';
        vars->player_x = new_x;
        vars->player_y = new_y;
        return (1);
    }
    return (0);
}

int handle_keypress(int keycode, t_vars *vars)
{
    int moved = 0;

    if (keycode == ESC)
        exit_game(vars);
    else if ((keycode == UP_ARROW || keycode == W) && vars->map[vars->player_y - 1][vars->player_x] != '1')
        moved = move_player(vars, vars->player_x, vars->player_y - 1);
    else if ((keycode == DOWN_ARROW || keycode == S) && vars->map[vars->player_y + 1][vars->player_x] != '1')
        moved = move_player(vars, vars->player_x, vars->player_y + 1);
    else if ((keycode == LEFT_ARROW || keycode == A) && vars->map[vars->player_y][vars->player_x - 1] != '1')
        moved = move_player(vars, vars->player_x - 1, vars->player_y);
    else if ((keycode == RIGTH_ARROW || keycode == D) && vars->map[vars->player_y][vars->player_x + 1] != '1')
        moved = move_player(vars, vars->player_x + 1, vars->player_y);
    if (moved)
    {
        mlx_clear_window(vars->mlx, vars->win);
        draw_map(vars);
    }
    return (0);
}




