/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_placement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:45:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 13:43:22 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	coords_for_drawing(int x, int y, t_prm *prm)
{
	prm->xyz[2][X] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][X];
	prm->xyz[2][Y] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][Y];
	prm->xyz[1][X] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][X];
	prm->xyz[1][Y] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][Y];
	get_color(x, y, prm);
	get_z_height(x, y, prm);
	draw_line(prm);
}

static void	wireframe_image(t_prm *prm)
{
	prm->xyz[0][Y] = 0;
	while (prm->coord[prm->xyz[0][Y]])
	{
		prm->xyz[0][X] = 0;
		while (prm->coord[prm->xyz[0][Y]][prm->xyz[0][X]])
		{
			if (prm->xyz[0][X] > 0)
				coords_for_drawing(-1, 0, prm);
			if (prm->xyz[0][Y] > 0)
				coords_for_drawing(0, -1, prm);
			prm->xyz[0][X]++;
		}
		prm->xyz[0][Y]++;
	}
}

static void	clamp_location(t_prm *prm)
{
	int	y;
	int	x;
	int	x_temp;
	int	y_temp;

	y = 0;
	while (prm->coord_copy[y])
	{
		x = 0;
		while (prm->coord_copy[y][x])
		{
			x_temp = prm->coord_copy[y][x][X];
			y_temp = prm->coord_copy[y][x][Y];
			if (prm->x_extremes[0] < 0)
				prm->coord_copy[y][x][X] = x_temp + abs(prm->x_extremes[0]);
			else if (prm->x_extremes[1] > prm->win_x)
				prm->coord_copy[y][x][X] = x_temp - abs(prm->x_extremes[0]);
			if (prm->y_extremes[0] < 0)
				prm->coord_copy[y][x][Y] = y_temp + abs(prm->y_extremes[0]);
			else if (prm->y_extremes[1] > prm->win_y)
				prm->coord_copy[y][x][Y] = y_temp - abs(prm->y_extremes[0]);
			x++;
		}
		y++;
	}
}

static void	copy_numbers(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	while (prm->coord[y])
	{
		x = 0;
		while (prm->coord[y][x])
		{
			prm->coord_copy[y][x][0] = prm->coord[y][x][0];
			prm->coord_copy[y][x][1] = prm->coord[y][x][1];
			prm->coord_copy[y][x][2] = prm->coord[y][x][2];
			rotation_matrices(prm->coord_copy[y][x], prm);
			get_extremes(prm, x, y);
			x++;
		}
		y++;
	}
	clamp_location(prm);
}

void	pixel_placement(t_prm *prm)
{
	int	index;

	index = 0;
	while (index < prm->win_x * prm->win_y)
	{
		prm->z_buffer[index] = INT_MAX;
		index++;
	}
	copy_numbers(prm);
	if (prm->isfill == 1)
		fill_image(prm);
	wireframe_image(prm);
}
