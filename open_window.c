/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:45:38 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 14:26:00 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	xyz_default_scale(t_prm *prm)
{
	prm->scale_xyz[X] = 4;
	prm->scale_xyz[Y] = 4;
	prm->scale_xyz[Z] = 4;
	prm->scale_default[X] = prm->scale_xyz[X];
	prm->scale_default[Y] = prm->scale_xyz[Y];
	prm->scale_default[Z] = prm->scale_xyz[Z];
}

static int	calculate_window_size(int nb)
{
	int	index;
	int	temp;

	temp = nb;
	index = 1;
	while (index < 6 && index * 256 <= temp)
	{
		nb = index * 256;
		index++;
	}
	return (nb);
}

static void	window_size(t_prm *prm)
{
	int	temp1;
	int	temp2;

	prm->win_x = prm->scale_xyz[0] * prm->xyz[0][X] * 3;
	prm->win_x = calculate_window_size(prm->win_x);
	prm->win_y = prm->scale_xyz[1] * prm->xyz[0][Y] * 3;
	prm->win_y = calculate_window_size(prm->win_y);
	if (prm->win_x > calculate_window_size(1920))
		prm->win_x = calculate_window_size(1920);
	if (prm->win_y > calculate_window_size(1080))
		prm->win_y = calculate_window_size(1080);
	if (prm->win_x < calculate_window_size(640))
		prm->win_x = calculate_window_size(640);
	if (prm->win_y < calculate_window_size(480))
		prm->win_y = calculate_window_size(480);
	prm->loc_xyz[X] = 0;
	prm->loc_xyz[Y] = 0;
	temp1 = prm->xyz[0][X] * prm->scale_xyz[0];
	temp2 = prm->xyz[0][Y] * prm->scale_xyz[1];
	if (temp1 > prm->win_x || temp2 > prm->win_y)
		xyz_default_scale(prm);
}

static void	clamp_height(t_prm *prm)
{
	int		x;
	int		y;
	int		range;
	double	height;

	y = 0;
	while (prm->coord[y])
	{
		x = 0;
		while (prm->coord[y][x])
		{
			range = abs(prm->min_height) + abs(prm->max_height);
			height = prm->coord[y][x][Z];
			height = ((double)(height + abs(prm->min_height)) / range);
			prm->coord[y][x][Z] = height * range;
			x++;
		}
		y++;
	}
}

void	open_window(t_prm *prm)
{
	t_mlx	*mlx;

	mlx = prm->mlx;
	window_size(prm);
	clamp_height(prm);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, prm->win_x, prm->win_y, "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, prm->win_x, prm->win_y);
	mlx->image_add = \
	mlx_get_data_addr(mlx->image_ptr, &prm->bpp, &prm->size_line, &prm->erdian);
	prm->z_buffer = (int *)malloc(sizeof(int) * prm->win_x * prm->win_y);
	if (prm->z_buffer == NULL)
		exit_window(prm, "error", TRUE);
	mlx_loop_hook(mlx->mlx_ptr, mlx_window_loop, prm);
	mlx_key_hook(mlx->win_ptr, keycode_hook, prm);
	mlx_loop(mlx->mlx_ptr);
}
