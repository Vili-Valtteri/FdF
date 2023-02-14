/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:16:12 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/19 15:45:29 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_prm	prm;
	t_mlx	mlx;

	ft_bzero(&prm, sizeof(t_prm));
	prm.mlx = &mlx;
	ft_bzero(prm.mlx, sizeof(t_mlx));
	open_fd(argv[1], argc, &prm);
	read_file(&prm);
	open_window(&prm);
	return (0);
}
