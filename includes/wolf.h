/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:52:40 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 11:52:46 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../minilibx_macos/mlx.h"

# include <math.h>
# include <pthread.h>

# include "libft.h"
# include "get_next_line.h"


# include <stdio.h>


/**********//* map */
typedef	struct		s_map
{
	char			*type;
	int				first_in_row;
	int				x;
	int				y;
	struct	s_map 	*next;
}					t_map;
/**********//* utils */
typedef struct		s_xy
{
	double			dx;
	double			dy;
	int				x;
	int				y;
}					t_xy;
/**********//* texture */
typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;
/**********//* utils */
typedef struct		s_img
{
	void			*newi;
	char			*addr;
	int				sizel;
	int				bpp;
	int				endi;

	int				color;

}					t_img;
/**********//* raycaster */
typedef	struct		s_ray
{
	t_img			*env;
	t_img			*txt;
	t_img			*txt_floor;
	t_xy			floor;

	double			camera;
	int				wall;

	t_xy			pos;
	t_xy			dir;
	t_xy			plane;
	t_xy			dist;
	t_xy			delta;
	t_xy			step;

	int				l_start;
	int				l_end;
	int				l_h;

	double			wallx;
	double			t_x;
	double			t_y;
}					t_ray;
/**********//* utils */
typedef struct		s_movement
{
	double			forward;
	double			backward;
	double			step_left;
	double			step_right;
}					t_movement;
/**********//* utils */
typedef struct		s_win
{
	void			*mlx;
	void			*win;	
	t_img			**txts;
	
	t_img			*sky;

	t_map			*map;
	t_ray			**ray;

	t_xy			dir;
	t_xy			pos;

	double			mouse;
	t_movement		movement;

}					t_win;
			/* map/map_utils */
t_map		*map_new_node(char *type, int x, int y);
void		map_add_node(t_map **first_node, t_map *new_node);
void		map_del_all(t_map **node);
char		map_get_type(t_map *map, int x, int y);
t_xy		map_get_xy(t_map *map, char type);
			/* map/map_get_data */
t_map		*map_create(char *filename);
			/* map/map_validation */
int			map_valid_data(char *data);
int			map_catch_exception();
			/* map/map_exception */
void		map_exception(t_map	*m, char *msg);
			/* utils/xy */
t_xy		set_xy(double x, double y);
			/* utils/window */
t_win		*window_new(int w, int h, char *name);
void		window_map_init(t_win *win, char *map_file);
void		window_ray_init(t_win *win);
void		window_destroy(t_win *w);
void		window_exception(t_win *win, char *msg);
			/* utils/image */
t_img		*image_new(void *mlx, int w, int h, char *img_file);
void		image_destroy(void *mlx, t_img *img);
			/* raycaster/display */
int			out_of_range(int thr_id, t_xy xy);
int			get_thr_x(int thr_id, int x);
void		display(t_win *win, int thread_id, int x0, int xn);
			/* raycaster/raycast */
void		raycast(t_win *win, int thread_id, int x);
			/* raycaster/direction */
void		direction_win(t_win *win);
t_xy		dir_plane(t_xy plane, double vec);
t_xy		dir_rotate(t_xy dir, double vec);
			/* raycaster/position */
int			pos_is_it_floor(t_xy pos, t_xy dir, t_map *map, double keys);
t_xy		pos_move(t_xy pos0, t_xy dir, double keys);
void		position_win(t_win *win);
			/* utils/threads */
void		thread_make(t_win *win);
			/* utils/threads_image */
void		threads_set_image(t_win *win);
void		threads_put_image(t_win *win);
void		threads_reset_image(t_win *win);
void		threads_free_image(t_win *win);
			/*texture/txt_init*/
t_img		**txt_init(void *mlx);
void		txt_free(void *mlx, t_img **txts);
			/*texture/color*/
t_color		txt_color_get_addr(char *addr, int idx);
void		txt_color_shift_y(t_color *color);
void		txt_color_set_pixel(char *addr, int idx, t_color color);
			/*texture/txt_ray*/
void		txt_wallx(t_ray *ray, double dist);
void		txt_floor_direction(t_ray *ray);
			/*texture/txt_draw*/
void		txt_draw_wall(t_ray *ray, int thr_id, t_xy xy);
void		txt_draw_floor(t_ray *ray, int thr_id, t_xy xy);

# define COLOR_SKY 0xA9EAFF
# define COLOR_FLOOR 0x3A9D23
# define COLOR_NORTH 0x116CC7
# define COLOR_SOUTH 0xDD985C
# define COLOR_EAST 0xA91101
# define COLOR_WEST 0xEFD242

# define WIDTH 1280
# define WIDTH_1_4 (float)WIDTH * (1.0 / 4.0)
# define HEIGHT 720
# define THREADS 4
# define TXTS 5
# define TXT_H 200
# define TXT_W 200

# define I (int)

# define SKY_T "textures/star_sky.xpm"

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

# define MOVE_SPEED 0.1
# define MOUSE_SPEED 0.5

#endif
