/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 03:35:07 by ablizniu          #+#    #+#             */
/*   Updated: 2019/06/23 15:19:18 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static double	ft_calc_angle(double x1, double y1, double x2, double y2)
{
	double		result;

	result = (x1 * y1 + x2 * y2) / (sqrt(pow(x1, 2) + pow(x2, 2)) *
	sqrt(pow(y1, 2) + pow(y2, 2)));
	return (acos(result) * ANG / M_PI);
}

void			ft_draw_sprite(t_main *m, int32_t x, int32_t y, double cam)
{
	double		len;
	t_iter		iter;
	int32_t		sv;
	int			*col;

	len = 200.0;
	sv = y;
	iter.x = 0;
	iter.y = 0;
	iter.dx = m->sprite.ch->w / (len - cam);
	iter.dy = m->sprite.ch->h / (len - cam);
	while (iter.y * iter.dy < m->sprite.ch->w)
	{
		iter.x = 0;
		y = sv;
		while (iter.x * iter.dx < m->sprite.ch->h)
		{
			GET_COLOR(col, m->sprite.ch->pixels, (int32_t)(iter.x * iter.dx),
					m->sprite.ch->pitch, (int32_t)(iter.y * iter.dy),
					m->sprite.ch->format->BytesPerPixel);
			if (*col != 0x008080)
				ft_put_pixel(m, x, y, *col);
			iter.x++;
			y++;
		}
		x++;
		iter.y++;
	}
}

void			ft_sprite(t_main *m)
{
	t_iter		iter;
	double		angle;
	t_vertex	pos;
	int			w;

	w = 0;
	iter.y = HALFHEIGTH;
	iter.x = 200;
	angle = ft_calc_angle(pos.x - m->player.pos.x, pos.y - m->player.pos.y,
			m->spr_data.pos.x - m->player.pos.x,
			m->spr_data.pos.y - m->player.pos.y);
	m->spr_data.anglee = angle;
	pos.x = 1.0;
	pos.y = 1.0;
	if (angle < 33.0 && m->eventcall.eee == 0)
	{
		while (w < WIDTH)
		{
			if (floor(angle) == floor(m->spr_data.angle[w]))
			{
				ft_draw_sprite(m, w, iter.y, m->spr_data.dist[w]);
				break ;
			}
			w++;
		}
	}
}
