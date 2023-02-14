/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:34:00 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 12:07:00 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	new_list(t_prm *prm, t_fdf *elem)
{
	elem->next = malloc(sizeof(t_fdf));
	if (elem->next == NULL)
		exit_window(prm, "error", TRUE);
	elem->next->next = NULL;
}

static void	copy_gnl_line(t_prm *prm, t_fdf *elem, char *line)
{
	elem->line = ft_strnew(ft_strlen(line));
	if (elem->line == NULL)
		exit_window(prm, "error", TRUE);
	ft_strcpy(elem->line, line);
	ft_bzero(line, ft_strlen(line));
	free(line);
	prm->xyz[0][X]++;
}

static void	gnl_file(t_prm *prm)
{
	int		gnl;
	char	*line;
	t_fdf	*elem;

	gnl = 1;
	elem = prm->head;
	while (gnl > 0)
	{
		gnl = get_next_line(prm->fd, &line);
		if (gnl > 0)
		{
			if (prm->xyz[0][X] != 0)
				new_list(prm, elem);
			if (prm->xyz[0][X] != 0)
				elem = elem->next;
			copy_gnl_line(prm, elem, line);
		}
	}
	if (elem == prm->head)
		exit_window(prm, "error", TRUE);
}

void	read_file(t_prm *prm)
{
	t_fdf	head;
	int		gnl;

	ft_bzero(&head, sizeof(t_fdf));
	prm->head = &head;
	gnl = 1;
	prm->erdian = 1;
	prm->xyz[0][X] = 0;
	gnl_file(prm);
	error_check(prm);
	prm->coord = (int ***)malloc((prm->xyz[0][X] + 1) * sizeof(int **));
	prm->coord_copy = (int ***)malloc((prm->xyz[0][X] + 1) * sizeof(int **));
	if (prm->coord == NULL || prm->coord_copy == NULL)
		exit_window(prm, "error", TRUE);
	prm->coord[prm->xyz[0][X]] = NULL;
	prm->coord_copy[prm->xyz[0][X]] = NULL;
	malloc_coordinates(prm);
}
