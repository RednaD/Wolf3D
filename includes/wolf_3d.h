/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:09:45 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/27 17:02:43 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include "../libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
// # include "../SDL2-2.0.8/include/SDL.h"

# define WIDTH 600
# define HEIGHT 400
# define THREAD 1
# define MAX_FUNC 4
# define SQUARE 16
# define UP key == 126 || key == 13
# define DOWN key == 125 || key == 1
# define LEFT key == 123 || key == 0
# define RIGHT key == 124 || key == 2
# define SHIFT key = 56 || key == 60
# define ESCAPE key != 53

# define NB_FLOOR 1 //3
# define NB_WALL 4
# define NB_CEILING 1

typedef	struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct s_texture
{
	int			x;
	int			y;
	void		*p_img;
	unsigned int	*data;
	int			bpp;
	int			size;
	int			endian;
}				t_texture;

typedef struct	s_player
{
	long double	pos_x;
	long double pos_y;
	long double	dir_x;
	long double	dir_y;
	long double plane_x;
	long double	plane_y;
	long double	rot;
	long double	speed;
}				t_player;

typedef	struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_rayon
{
	long double	dir_x;
	long double	dir_y;
	int			map_x; //coord de la case dans lequel le rayon se trouve (ray_x)
	int			map_y; //coord de la case dans lequel le rayon se trouve (ray_y)
	long double	sidedist_x; // distance que le rayon a parcouru depuis la position du joueur
	long double	sidedist_y;
	long double	delta_x; // distance que le rayon doit parcourir pour passer d'une case a l'autre
	long double	delta_y;
	long double	w_dist; //longueur totale du rayon
}				t_rayon;

typedef	struct	s_local
{
	long double cam_x;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	long double	wall_x;
	long double	wall_pos_x;
	long double	wall_pos_y;
	long double	floor_x;
	long double	floor_y;
	long double	pl_dist;
	long double	cur_dist;
	long double	cur_pos;
	long double	cur_x;
	long double	cur_y;
	int			t_type;
	int			t_id;
	int			t_x;
	int			t_y;
	
}				t_local;

typedef struct	s_global
{
	t_texture	tex[3][4];
	t_rayon		ray;
	t_player	player;
	int			fd;
	void 		*mlx;
	void		*win;
	void		*p_img;
	unsigned int *data;
	int			bpp;
	int			size;
	int			endian;
	char		*name;
	int			**map;
	int			max_x;
	int			max_y;
	long		time;
	long		old_time;
	int			color;
	int			(*key_func[MAX_FUNC])(struct s_global*, int);
	int			len_key;
	int			bonus_tex;
	pthread_t	thread[THREAD];
}				t_global;

void			buh(t_global *g);
int				check_map(t_global *g);
void			check_start_pos(t_global *g);
int				close_map(t_global *global, int key);
int				deal_key(int key, t_global *global);
void			draw_segment(float *coord_src, float *coord_dst, \
															t_global *global);
void			draw_white_square(int x, int y, t_global *global);
void			draw_black_square(int x, int y, t_global *global);
void			free_parse(int **wall, int len_array);
int   			get_dir(t_global *g, int key);
int    			get_pos(t_global *g, int key);
int				sprint(t_global *g, int key);
int				close_mouse(int key, t_global *g);
void			init_map(t_global *g);
void			init_global(t_global *g);
void			mlx_pixel_put_to_image(t_global *global, int x, int y, \
																	int color);
// void			launch_mini_map(t_global *global);
void			raycast_loop(int x, int end, t_global *g);
void			texture(t_global *global);

#endif
