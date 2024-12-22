#ifndef SO_LONG_H
#define SO_LONG_H

#define BUFFER_SIZE 1024

# define WALLS '1'
# define FLOOR '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define START_POS 'P'

# define W 119
# define A 97
# define S 115
# define D 100

# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define DOWN_ARROW 65364
# define RIGTH_ARROW 65363
# define ESC 65307

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GREEN_COLOR 0x0000FF00

//# include "libft/libft.h"
//# include "printf/ft_printf.h"
# include "so_long.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"

typedef struct s_vars
{
    int fd;
    int player_count;
    int collectible_count;
    int exit_count;

    void    *mlx;
    void    *win;
    void    *player_img;
    void    *collectible_img;
    void    *exit_img;
    void    *floor_img;
    void    *wall_img;
    char    **map;
    char    *map_file; // pointer to a file path like "maps/map_1.ber"
    int     img_width;
    int     img_height;
    int     player_x;
    int     player_y;
    int     width;
    int     height;
} t_vars;


/*void	*mlx_init(void);
void	*mlx_new_window(void *mlx, int width, int height, char *title);
void	*mlx_new_image(void *mlx, int width, int height);
char    *mlx_get_data_addr(void *img, int *bits_per_pixel, int *line_length, int *endian);
int		mlx_pixel_put(void *mlx, void *win, int x, int y, int color);
int		mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);
int		mlx_loop(void *mlx);
int     mlx_hook(void *win, int event_type, int event_mask, int (*event_func)(), void *param);*/


// keycodes
int     handle_keypress(int keycode, t_vars *vars);

// errors
void check_counts(t_vars *vars);
void	character_valid(t_vars *vars);
void	check_errors(t_vars *vars);

// file name
int check_map_name(char *map_name);

// valid path
//int	map_checker(t_vars *game);

// exit~
void free_map_memory(t_vars *vars);
void destroy_images_and_exit(t_vars *vars);
void exit_game(t_vars *vars);

// graphics
void put_player(t_vars *vars, int width, int height);
void put_collectable(t_vars *vars, int width, int height);
void put_exit(t_vars *vars, int width, int height);
void load_images(t_vars *vars);
void draw_map(t_vars *vars);
int	map_reading(t_vars *vars);

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
int		buffer_clear(char *line);
char	*free_buf(char *buf);
char	*get_next_line(int fd);



#endif

