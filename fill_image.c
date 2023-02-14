/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:50:42 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 14:26:26 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	save_coordinates(int *x, int *y, t_prm *prm)
{
		prm->xyz[1][X] = x[0];
		prm->xyz[1][Y] = y[0];
		prm->xyz[2][X] = x[2];
		prm->xyz[2][Y] = y[2];
}

static int	fillin_image(int *x, int *y, t_prm *prm)
{
	t_brez	brez_line_a;
	t_brez	brez_line_b;
	int		result_a;
	int		result_b;

	result_a = 1;
	result_b = 1;
	brez_swap(x, y, &brez_line_a);
	brez_swap(&x[2], &y[2], &brez_line_b);
	while (result_a == 1 && result_b == 1)
	{
		save_coordinates(x, y, prm);
		if (y[0] == y[2])
			draw_line(prm);
		while (result_a == 1 && y[0] <= y[2])
			result_a = brez_pixel(x, y, &brez_line_a);
		while (result_b == 1 && y[2] < y[0])
			result_b = brez_pixel(&x[2], &y[2], &brez_line_b);
	}
	if (result_a == 1)
		return (1);
	return (0);
}

static void	image_functions(int *triangle, t_prm *prm)
{
	int	x[4];
	int	y[4];
	int	fillin;

	x[0] = triangle[0];
	y[0] = triangle[1];
	x[1] = triangle[3];
	y[1] = triangle[4];
	x[2] = triangle[0];
	y[2] = triangle[1];
	x[3] = triangle[6];
	y[3] = triangle[7];
	fillin = fillin_image(x, y, prm);
	x[0] = triangle[3];
	y[0] = triangle[4];
	x[1] = triangle[6];
	y[1] = triangle[7];
	x[3] = triangle[6];
	y[3] = triangle[7];
	fillin_image(x, y, prm);
}

void	fill_image(t_prm *prm)
{
	int	triangle[9];

	prm->xyz[0][Y] = 0;
	while (prm->coord[prm->xyz[0][Y]])
	{
		prm->xyz[0][X] = 0;
		while (prm->coord[prm->xyz[0][Y]][prm->xyz[0][X]])
		{
			if (prm->xyz[0][Y] > 0 && prm->xyz[0][X] > 0)
			{
				triangle_coords(0, -1, triangle, prm);
				image_functions(triangle, prm);
				triangle_coords(-1, 0, triangle, prm);
				image_functions(triangle, prm);
			}
			prm->xyz[0][X]++;
		}
		prm->xyz[0][Y]++;
	}
}
