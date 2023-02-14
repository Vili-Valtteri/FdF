/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:58:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 12:56:10 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define KEY_W 13
# define KEY_X 7
# define KEY_C 8
# define KEY_Y 16
# define KEY_U 32
# define KEY_F 3
# define KEY_R 15
# define KEY_ESC 53
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define TRUE 1
# define FALSE 0
# define BOOL int
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_prm
{
	struct s_mlx		*mlx;
	struct s_brez_line	*brez_var;
	struct s_fdf		*head;
	double				alpha;
	double				beta;
	int					fd;
	int					loc_xyz[6];
	int					scale_xyz[3];
	int					scale_default[3];
	int					xyz[3][3];
	int					min_height;
	int					max_height;
	int					z_extremes[2];
	int					y_extremes[2];
	int					x_extremes[2];
	int					win_x;
	int					win_y;
	int					***coord;
	int					***coord_copy;
	int					*z_buffer;
	int					bpp;
	int					size_line;
	int					erdian;
	int					isfill;
	unsigned int		color;
	unsigned int		colorwhite;
}						t_prm;

typedef struct s_brez_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e2;
	int				error;
}					t_brez;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
}				t_mlx;

typedef struct s_fdf
{
	char			*line;
	struct s_fdf	*next;
}					t_fdf;

void	rotation_matrices(int *vector3, t_prm *prm);
void	sort_coordinates(t_prm *prm);
void	pixel_placement(t_prm *prm);
void	read_file(t_prm *prm);
void	free_all(t_prm *prm, char *error_msg, BOOL error);
void	free_prm(t_prm *prm);
void	free_fdf(t_fdf *head);
int		keycode_hook(int key, void *prm);
void	open_fd(char *file, int argc, t_prm *prm);
int		mlx_window_loop(void *prm);
void	open_window(t_prm *prm);
void	fill_image(t_prm *prm);
void	draw_line(t_prm *prm);
void	malloc_coordinates(t_prm *prm);
void	get_color(int x, int y, t_prm *prm);
void	get_z_height(int x, int y, t_prm *prm);
void	triangle_coords(int x, int y, int *triangle, t_prm *prm);
void	brez_swap(int *x, int *y, t_brez *brez_var);
int		brez_pixel(int *x, int *y, t_brez *brez_var);
void	error_check(t_prm *prm);
void	exit_window(t_prm *prm, char *error_msg, BOOL error);
void	get_extremes(t_prm *prm, int x, int y);
int		clamp_max_min_z(int nb);

#endif
