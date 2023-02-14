/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:39:26 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 12:46:09 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	setup_settings(t_prm *prm)
{
	prm->scale_xyz[0] = 20;
	prm->scale_xyz[1] = 20;
	prm->scale_xyz[2] = 20;
	prm->scale_default[X] = prm->scale_xyz[X];
	prm->scale_default[Y] = prm->scale_xyz[Y];
	prm->scale_default[Z] = prm->scale_xyz[Z];
	prm->isfill = 0;
	prm->colorwhite = 0;
}

void	open_fd(char *file, int argc, t_prm *prm)
{
	if (argc != 2)
		exit_window(prm, "usage ./fdf matrix_file", TRUE);
	prm->fd = open(file, O_RDONLY);
	if (prm->fd == -1)
		exit_window(prm, "error", TRUE);
	setup_settings(prm);
}
