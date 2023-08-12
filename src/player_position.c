/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:14:08 by ayaman            #+#    #+#             */
/*   Updated: 2023/06/15 17:49:19 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_game *game, int i, int j)
{
	game->ray.posx = i + 0.5;
	game->ray.posy = j + 0.5;
	game->ray.dirx = 0;
	game->ray.diry = 0;
	game->ray.planex = 0;
	game->ray.planey = 0;
}

/*
	burayı rafet veya başka birine sor.
*/

void	player_position(t_game *game, int i, int j)
{
	game->ray.posx = i + 0.5;
	game->ray.posy = j + 0.5;
	if (game->map[i][j] == 'E')
	{
		game->ray.diry = 1;
		game->ray.planex = 0.66;
	}
	else if (game->map[i][j] == 'W')
	{
		game->ray.diry = -1;
		game->ray.planex = -0.66;
	}
	else if (game->map[i][j] == 'S')
	{
		game->ray.dirx = 1;
		game->ray.planey = -0.66;
	}
	else if (game->map[i][j] == 'N')
	{
		game->ray.dirx = -1;
		game->ray.planey = 0.66;
	}
}
