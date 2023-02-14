/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:42:41 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 12:47:23 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_prm(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	while (prm->coord[y])
	{
		x = 0;
		while (prm->coord[y][x])
		{
			free(prm->coord_copy[y][x]);
			free(prm->coord[y][x]);
			x++;
		}
		free(prm->coord_copy[y]);
		free(prm->coord[y]);
		y++;
	}
	free(prm->coord);
	free(prm->coord_copy);
	free(prm->z_buffer);
	mlx_destroy_image(prm->mlx->mlx_ptr, prm->mlx->image_ptr);
}

void	free_fdf(t_fdf *head)
{
	t_fdf	*hold;

	if (head->line)
		free(head->line);
	head = head->next;
	while (head)
	{
		hold = head->next;
		if (head->line)
			free(head->line);
		free(head);
		head = hold;
	}
}

void	exit_window(t_prm *prm, char *error_msg, BOOL error)
{
	if (prm->head)
		free_fdf(prm->head);
	if (error == TRUE && error_msg)
		ft_putendl_fd(error_msg, 2);
	exit(0);
}
