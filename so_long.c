#include "so_long.h"

static void	*ftt_memset(void *b, int c, size_t length)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (length--)
		*p++ = (unsigned char)c;
	return (b);
}

int main(int argc, char **argv)
{
    t_vars vars;

    if (argc != 2)
        return (1);
    if (check_map_name(argv[1]))
        return (1);
    ftt_memset(&vars, 0, sizeof(t_vars));
    vars.map_file = argv[1];
    if (!map_reading(&vars))
        return (1);
    check_errors(&vars);
    /*if (!map_checker(&vars))
	{
		printf("Error: Map contains invalid characters.\n");
		return (1);
	}*/
    printf("Map loaded successfully.\n");
    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (1);
    vars.win = mlx_new_window(vars.mlx, 1920, 800, "Game so_long");
    if (!vars.win)
        return (1);
    load_images(&vars);
    draw_map(&vars);
    mlx_hook(vars.win, 17, 0, (void *)exit_game, &vars);
    mlx_key_hook(vars.win, handle_keypress, &vars);
    mlx_loop(vars.mlx);
    return (0);
}

