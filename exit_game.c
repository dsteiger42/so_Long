#include "so_long.h"

void free_map_memory(t_vars *vars)
{
    int i = 0;

    if (vars->map)
    {
        while (i < vars->height)
        {
            free(vars->map[i]);
            i++;
        }
        free(vars->map);
    }
}

void destroy_images_and_exit(t_vars *vars)
{
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    if (vars->player_img)
        mlx_destroy_image(vars->mlx, vars->player_img);
    if (vars->collectible_img)
        mlx_destroy_image(vars->mlx, vars->collectible_img);
    if (vars->exit_img)
        mlx_destroy_image(vars->mlx, vars->exit_img);
    if (vars->wall_img)
        mlx_destroy_image(vars->mlx, vars->wall_img);
    if (vars->floor_img)
        mlx_destroy_image(vars->mlx, vars->floor_img);
    if (vars->mlx)
    {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
    }
    printf("Game exited successfully.\n");
    exit(0);
}

void exit_game(t_vars *vars)
{
    free_map_memory(vars);
    destroy_images_and_exit(vars);
}

