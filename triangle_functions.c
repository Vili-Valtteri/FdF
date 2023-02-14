/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:20:32 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 14:26:53 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_xyz(int *ptr1, int *ptr2)
{
	int	temp[3];

	temp[0] = ptr1[0];
	temp[1] = ptr1[1];
	temp[2] = ptr1[2];
	ptr1[0] = ptr2[0];
	ptr1[1] = ptr2[1];
	ptr1[2] = ptr2[2];
	ptr2[0] = temp[0];
	ptr2[1] = temp[1];
	ptr2[2] = temp[2];
}

static void	sort_triangle(int *triangle)
{
	if (triangle[1] > triangle[4])
	{
		swap_xyz(&triangle[0], &triangle[3]);
		if (triangle[1] > triangle[7])
			swap_xyz(&triangle[0], &triangle[6]);
	}
	else if (triangle[1] > triangle[7])
	{
		swap_xyz(&triangle[0], &triangle[6]);
	}
	if (triangle[7] < triangle[4])
		swap_xyz(&triangle[6], &triangle[3]);
}

void	triangle_coords(int x, int y, int *triangle, t_prm *prm)
{
	triangle[0] = prm->coord_copy[prm->xyz[0][Y] - 1][prm->xyz[0][X] - 1][0];
	triangle[1] = prm->coord_copy[prm->xyz[0][Y] - 1][prm->xyz[0][X] - 1][1];
	triangle[2] = prm->coord_copy[prm->xyz[0][Y] - 1][prm->xyz[0][X] - 1][2];
	triangle[3] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][0];
	triangle[4] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][1];
	triangle[5] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][2];
	triangle[6] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][0];
	triangle[7] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][1];
	triangle[8] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][2];
	sort_triangle(triangle);
	get_color(x, y, prm);
	get_z_height(x, y, prm);
}
