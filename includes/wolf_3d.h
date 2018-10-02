/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:09:45 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/02 16:18:24 by arusso           ###   ########.fr       */
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

# define WIDTH 512
# define HEIGHT 512
# define WIDTH_UI 50
# define HEIGHT_UI 50
# define THREAD 8
# define SQUARE 16
# define FLOOR "textures/floor.xpm"
# define WALL "textures/wall.xpm"
# define CEILING "textures/ceiling.xpm"

typedef	struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct s_texture
{
	int		x;
	int		y;
	void	*p_img;
	char	*img_addr;
	int		bpp;
	int		size;
	int		endian;
}				t_texture;

// typedef struct	s_map
// {
// 	void	*p_img;
// 	char	*img_addr;
// 	int		bpp;
// 	int		size;
// 	int		endian;
// }				t_map;

typedef struct	s_player
{
	long double		pos_x;
	long double 	pos_y;
	long double		dir_x;
	long double		dir_y;
	long double 	plane_x;
	long double		plane_y;
}				t_player;

typedef struct	s_global
{
	t_texture	wall;
	t_texture	ceiling;
	t_texture	floor;
	// t_map		mini_map;
	t_player	player;
	int			fd;
	void 		*mlx;
	void		*win;
	void		*p_img;
	char		*img_addr;
	int			bpp;
	int			size;
	int			endian;
	char		*name;
	int			**map;
	int			map_x;
	int			map_y;
	int			x_init;
	int			y_init;
	long		time;
	long		old_time;
	// int			color; couleur pour mini_map
	int			(*key_func[1])(struct s_global*, int);
	int			len_key;
	pthread_t	thread[THREAD];
}				t_global;

int				check_map(t_global *g);
void			check_start_pos(t_global *g);
int				close_map(t_global *global, int key);
int				deal_key(int key, t_global *global);
void			draw_segment(float *coord_src, float *coord_dst, \
															t_global *global);
void			draw_white_square(int x, int y, t_global *global);
void			draw_black_square(int x, int y, t_global *global);
void			free_parse(int **wall, int len_array);
void			init_map(t_global *g);
void			init_global(t_global *g);
void			mlx_pixel_put_to_image(t_global *global, int x, int y, \
																	int color);
// void			launch_mini_map(t_global *global);
void			print_parse(t_global *global);
void			raycast_loop(t_global *global);
void			texture(t_global *global);

#endif
