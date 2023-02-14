/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:29:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/22 12:43:57 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	line_parser(char *str)
{
	char	ch;
	int		index;
	int		x;

	index = 0;
	x = 0;
	ch = 'a';
	while (str[index] && index >= 0)
	{
		if (ch == '-' && ft_isdigit(str[index]) == 0)
			index = -2;
		ch = str[index];
		if (ft_isdigit(ch) == 0 && ft_isspace(ch) == 0 && ch != '-')
			index = -2;
		if (ft_isspace(ch) == 0 && (index == 0 || ft_isspace(str[index - 1])))
			x++;
		index++;
	}
	if (index <= 1)
		return (-1);
	if (ch == '-')
		return (-1);
	return (x);
}

void	error_check(t_prm *prm)
{
	t_fdf	*elem;
	int		last_index;
	int		index;

	elem = prm->head;
	index = 0;
	last_index = -1;
	while (elem)
	{
		index = line_parser(elem->line);
		if (last_index == -1)
			last_index = index;
		if (last_index != index || index < 0)
			exit_window(prm, "error", TRUE);
		elem = elem->next;
	}
	if (!prm->head->next || index < 2)
		exit_window(prm, "error", TRUE);
}
