/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brez_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:19:14 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 10:55:59 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	brez_while_conditions(t_prm *prm)
{
	t_brez	*brez_var;

	brez_var = prm->brez_var;
	if (prm->xyz[1][X] == prm->xyz[2][X] && prm->xyz[1][Y] == prm->xyz[2][Y])
		return (0);
	brez_var->e2 = 2 * brez_var->error;
	if (brez_var->e2 >= brez_var->dy)
	{
		if (prm->xyz[1][X] == prm->xyz[2][X])
			return (0);
		brez_var->error = brez_var->error + brez_var->dy;
		prm->xyz[1][X] = prm->xyz[1][X] + brez_var->sx;
	}
	if (brez_var->e2 <= brez_var->dx)
	{
		if (prm->xyz[1][Y] == prm->xyz[2][Y])
			return (0);
		brez_var->error = brez_var->error + brez_var->dx;
		prm->xyz[1][Y] = prm->xyz[1][Y] + brez_var->sy;
	}
	return (1);
}

static void	brez_while(t_prm *prm)
{
	t_brez	*brez_var;
	int		pic_size;

	brez_var = prm->brez_var;
	while (1)
	{
		pic_size = (prm->size_line / 4) * prm->xyz[1][Y];
		pic_size = pic_size + prm->xyz[1][X];
		if (pic_size < prm->win_x * prm->win_y && pic_size > 0)
		{
			if (prm->xyz[0][Z] < prm->z_buffer[pic_size] && \
			prm->xyz[1][X] < prm->win_x && prm->xyz[1][X] >= 0)
			{
				if (prm->colorwhite == 1)
					prm->color = INT_MAX;
				prm->z_buffer[pic_size] = prm->xyz[0][Z];
				((unsigned int *)prm->mlx->image_add)[pic_size] = prm->color;
			}
		}
		if (brez_while_conditions(prm) == 0)
			break ;
	}
}

void	draw_line(t_prm *prm)
{
	t_brez	brez_var;

	ft_bzero(&brez_var, sizeof(t_brez));
	prm->xyz[1][X] = prm->xyz[1][X] + prm->loc_xyz[X];
	prm->xyz[2][X] = prm->xyz[2][X] + prm->loc_xyz[X];
	prm->xyz[1][Y] = prm->xyz[1][Y] + prm->loc_xyz[Y];
	prm->xyz[2][Y] = prm->xyz[2][Y] + prm->loc_xyz[Y];
	brez_var.dx = abs(prm->xyz[2][X] - prm->xyz[1][X]);
	if (prm->xyz[1][X] < prm->xyz[2][X])
		brez_var.sx = 1;
	else
		brez_var.sx = -1;
	brez_var.dy = -abs(prm->xyz[2][Y] - prm->xyz[1][Y]);
	if (prm->xyz[1][Y] < prm->xyz[2][Y])
		brez_var.sy = 1;
	else
		brez_var.sy = -1;
	brez_var.error = brez_var.dx + brez_var.dy;
	prm->brez_var = &brez_var;
	brez_while(prm);
}

int	brez_pixel(int *x, int *y, t_brez *brez_var)
{
	int	fx;
	int	fy;

	fx = x[0];
	fy = y[0];
	if (x[0] == x[1] && y[0] == y[1])
		return (0);
	brez_var->e2 = 2 * brez_var->error;
	if (brez_var->e2 >= brez_var->dy)
	{
		brez_var->error = brez_var->error + brez_var->dy;
		x[0] = x[0] + brez_var->sx;
	}
	if (brez_var->e2 <= brez_var->dx)
	{
		brez_var->error = brez_var->error + brez_var->dx;
		y[0] = y[0] + brez_var->sy;
	}
	if (fx != x[0] || fy != y[0])
		return (1);
	return (0);
}

void	brez_swap(int *x, int *y, t_brez *brez_var)
{
	brez_var->dx = abs(x[1] - x[0]);
	if (x[0] < x[1])
		brez_var->sx = 1;
	else
		brez_var->sx = -1;
	brez_var->dy = -abs(y[1] - y[0]);
	if (y[0] < y[1])
		brez_var->sy = 1;
	else
		brez_var->sy = -1;
	brez_var->error = brez_var->dx + brez_var->dy;
}
