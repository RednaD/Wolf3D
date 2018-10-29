/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:09:45 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/26 17:26:49 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include "../libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>

# define WIDTH 1600
# define HEIGHT 900
# define THREAD 8
# define SQUARE 4
# define UP key == 126 || key == 13
# define DOWN key == 125 || key == 1
# define LEFT key == 123 || key == 0
# define RIGHT key == 124 || key == 2
# define SHIFT key == 257 || key == 258
# define T key == 17
# define ESCAPE key == 53

# define NB_FLOOR 1
# define NB_WALL 4
# define NB_CEILING 1

typedef	struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_texture
{
	int				x;
	int				y;
	void			*p_img;
	unsigned int	*data;
	int				bpp;
	int				size;
	int				endian;
}					t_texture;

typedef struct		s_player
{
	long double		pos_x;
	long double		pos_y;
	long double		dir_x;
	long double		dir_y;
	long double		plane_x;
	long double		plane_y;
	long double		rot;
	long double		speed;
}					t_player;

typedef	struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_rayon
{
	long double		dir_x;
	long double		dir_y;
	int				map_x; //coord de la case dans lequel le rayon se trouve (ray_x)
	int				map_y; //coord de la case dans lequel le rayon se trouve (ray_y)
	long double		sidedist_x; // distance que le rayon a parcouru depuis la position du joueur
	long double		sidedist_y;
	long double		delta_x; // distance que le rayon doit parcourir pour passer d'une case a l'autre
	long double		delta_y;
	long double		w_dist; //longueur totale du rayon
}					t_rayon;

typedef	struct		s_local
{
	t_rayon			ray;
	long double		cam_x;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	long double		wall_x;
	long double		wall_pos_x;
	long double		wall_pos_y;
	long double		floor_x;
	long double		floor_y;
	long double		pl_dist;
	long double		cur_dist;
	long double		cur_pos;
	long double		cur_x;
	long double		cur_y;
	int				t_type;
	int				t_id;
	int				t_x;
	int				t_y;

}					t_local;

typedef struct		s_mini_map
{
	void			*p_img;
	char			*data;
	int				bpp;
	int				size;
	int				endian;
}					t_mini_map;

typedef struct		s_input
{
	int				up;
	int				down;
	int				left;
	int				right;
}					t_input;

typedef struct		s_global
{
	t_texture		tex[3][4];
	t_player		player;
	t_mini_map		mini_map;
	t_input			input;
	int				fd;
	void			*mlx;
	void			*win;
	void			*p_img;
	unsigned int	*data;
	int				bpp;
	int				size;
	int				endian;
	char			*name;
	int				**map;
	int				max_x;
	int				max_y;
	int				bonus_tex;
	pthread_t		thread[THREAD];
}					t_global;

int					start_wolf(t_global *g);
int					check_map(t_global *g);
void				check_start_pos(t_global *g);
int					deal_key(int key, t_global *global);
int					deal_key_release(int key, t_global *g);
char				*get_path(int i, char *type);
int					get_thread_id(pthread_t id, pthread_t *thread);
void				init_map(t_global *g);
void				init_global(t_global *g);
void				mlx_pixel_put_to_image(t_global *global, int x, int y, \
																	int color);
void				launch_mini_map(t_global *global);
void				set_coord(t_global *g, t_local *l, int x);
void				texture(t_global *global);
void				update_input(t_global *g);

#endif
