/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:45:20 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 11:35:16 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	str_to_int(char *str, t_prm *prm)
{
	int		index;

	index = 0;
	while (ft_isdigit(str[index]) == 1 || (index == 0 && str[index] == '-'))
		index++;
	if ((index > 10 && str[0] != '-') || index > 11)
		exit_window(prm, "error", TRUE);
	index = ft_atoi(str);
	return (index);
}

static void	set_coords(t_prm *prm, int z)
{
	int	x;
	int	y;

	x = prm->xyz[0][X];
	y = prm->xyz[0][Y];
	z = clamp_max_min_z(z);
	prm->coord[y][x] = (int *)malloc(sizeof(int) * 3);
	prm->coord_copy[y][x] = (int *)malloc(sizeof(int) * 3);
	if (prm->coord[y][x] == NULL || prm->coord_copy[y][x] == NULL)
		exit_window(prm, "error", TRUE);
	prm->coord[y][x][0] = x;
	prm->coord[y][x][1] = y;
	prm->coord[y][x][2] = z;
	if (z > prm->max_height)
		prm->max_height = z;
	if (z < prm->min_height)
		prm->min_height = z;
}

static void	gnl_line_len(t_prm *prm, t_fdf *elem)
{
	int		index;
	int		x;
	int		y;
	char	ch;

	x = prm->xyz[0][X];
	y = prm->xyz[0][Y];
	index = 0;
	x = 0;
	while (elem->line[index])
	{
		ch = elem->line[index];
		if (index > 0)
			if (ft_isspace(ch) == 0 && ft_isspace(elem->line[index - 1]))
				x++;
		if (index == 0 && ft_isspace(ch) == 0)
			x++;
		index++;
	}
	prm->coord[y] = (int **)malloc((x + 1) * sizeof(int *));
	prm->coord_copy[y] = (int **)malloc((x + 1) * sizeof(int *));
	if (prm->coord[y] == NULL || prm->coord_copy[y] == NULL)
		exit_window(prm, "error", TRUE);
	prm->coord[y][x] = NULL;
	prm->coord_copy[y][x] = NULL;
}

static void	gnl_line_to_coords(t_prm *prm, t_fdf *elem)
{
	int		index;
	char	ch;

	index = 0;
	prm->xyz[0][X] = 0;
	while (elem->line[index])
	{
		ch = elem->line[index];
		if (ft_isdigit(ch) == 0 && ft_isspace(ch) == 0 && ch != '-')
			exit_window(prm, "error", TRUE);
		if (ft_isspace(ch) == 0)
		{
			if (index == 0 || ft_isspace(elem->line[index - 1]))
			{
				set_coords(prm, str_to_int(&elem->line[index], prm));
				prm->xyz[0][X]++;
			}
		}
		index++;
	}
	prm->xyz[0][Y]++;
}

void	malloc_coordinates(t_prm *prm)
{
	t_fdf	*elem;

	elem = prm->head;
	prm->xyz[0][Y] = 0;
	while (elem)
	{
		gnl_line_len(prm, elem);
		gnl_line_to_coords(prm, elem);
		elem = elem->next;
	}
	free_fdf(prm->head);
	prm->head = NULL;
}
