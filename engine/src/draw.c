/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:36:20 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/23 15:17:54 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_get_border_bot(t_main *m, t_ray ray, t_heigth_wall *wall)
{
	if (ray.next_sect == -1)
	{
		wall->border_bot.flag = 0;
		return ;
	}
	if (m->sector[ray.num_sect].heigth.floor <
			m->sector[ray.next_sect].heigth.floor)
	{
		wall->diff_bord_bot = m->sector[ray.next_sect].heigth.floor -
				m->sector[ray.num_sect].heigth.floor;
		wall->border_bot.end = wall->end;
		wall->border_bot.start = wall->border_bot.end - wall->diff *
				wall->diff_bord_bot * 2;
		wall->border_bot.flag = 1;
		wall->border_b_h = wall->border_bot.end - wall->border_bot.start;
	}
	else
		wall->border_bot.flag = 0;
}

void			ft_get_floor(t_main *m, t_ray ray, t_heigth_wall *wall)
{
	ray.camdist = ray.camdist;
	m->player.sector = m->player.sector;
	if (wall->border_bot.flag == 0)
		wall->floor_h.start = wall->end;
	else
		wall->floor_h.start = wall->border_bot.end;
	wall->floor_h.end = HEIGHT;
	if (wall->floor_h.start < wall->floor_h.end)
		wall->floor_h.flag = 1;
	else
		wall->floor_h.flag = 0;
	wall->floor_h.floor_h = wall->floor_h.end - wall->floor_h.start;
}

void			ft_get_border_top(t_main *m, t_ray ray, t_heigth_wall *wall)
{
	if (ray.next_sect == -1)
	{
		wall->border_top.flag = 0;
		return ;
	}
	if (m->sector[ray.num_sect].heigth.cell >
			m->sector[ray.next_sect].heigth.cell)
	{
		wall->diff_bord_top = m->sector[ray.num_sect].heigth.cell -
				m->sector[ray.next_sect].heigth.cell;
		wall->border_top.start = wall->start;
		wall->border_top.end = wall->border_top.start +
				wall->diff * wall->diff_bord_top;
		wall->border_t_h = wall->border_top.end - wall->border_top.start;
		wall->border_top.flag = 1;
		if (ray.w == HALFWIDTH)
		{
			m->debug.top_start = wall->border_bot.start;
			m->debug.top_end = wall->border_bot.end;
		}
	}
	else
		wall->border_top.flag = 0;
}

void			ft_get_ceil(t_main *m, t_ray ray,
						t_heigth_wall *wall, t_buffer *buf)
{
	m->player.sector = m->player.sector;
	ray.camdist = ray.camdist;
	if (wall->border_top.flag == 0)
		wall->ceil_h.end = wall->start;
	else
		wall->ceil_h.end = wall->border_top.start;
	wall->ceil_h.start = buf->buffer_draw_top;
	if (wall->ceil_h.start < wall->ceil_h.end)
		wall->ceil_h.flag = 1;
	else
		wall->ceil_h.flag = 0;
}

inline void		ft_drawscreen(t_main *m, t_ray ray)
{
	t_heigth_wall		wall;
	t_buffer			buffer;
	static int32_t		border_b_h = 0;
	static int32_t		border_t_h = 0;
	static t_draw_save	sv_draw = {0, HEIGHT, 0};

	wall.border_b_h = 0;
	wall.border_t_h = 0;
	if (sv_draw.old_w != ray.w)
	{
		sv_draw.buffer_bot = HEIGHT;
		sv_draw.buffer_top = 0;
	}
	wall.dx = ray.wall_end.x - ray.wall_start.x;
	wall.dy = ray.wall_end.y - ray.wall_start.y;
	wall.y = (fabs(wall.dx) > fabs(wall.dy) ?
			(int)((ray.intersec.x - ray.wall_start.x) * 1000) :
			(int)((ray.intersec.y - ray.wall_start.y) * 1000)) %
			m->texture[0]->w;
	wall.old_border_b_h = border_b_h;
	wall.old_border_t_h = border_t_h;
	if (ray.camdist < 0.005)
		ray.camdist = 0.005;
	buffer.buffer_draw_bot = sv_draw.buffer_bot;
	buffer.buffer_draw_top = sv_draw.buffer_top;
	ft_get_wall_heigth(m, ray, &wall);
	ft_get_border_bot(m, ray, &wall);
	ft_get_border_top(m, ray, &wall);
	ft_get_floor(m, ray, &wall);
	ft_get_ceil(m, ray, &wall, &buffer);
	if (wall.floor_h.flag == 1)
		ft_draw_floor(m, ray, wall, &buffer);
	if (m->sector[ray.num_sect].transit[ray.wall_sect] == -1)
		ft_draw_wall(m, ray, wall, &buffer);
	if (wall.border_bot.flag == 1 || wall.border_top.flag == 1)
		ft_draw_border(m, ray, wall, &buffer);
	if (wall.ceil_h.flag == 1)
		ft_draw_cell(m, ray, wall, &buffer);
	border_b_h = wall.border_b_h;
	border_t_h = wall.border_t_h;
	sv_draw.buffer_bot = wall.end < buffer.buffer_draw_bot ?
			wall.end : buffer.buffer_draw_bot;
	sv_draw.buffer_top = wall.start > buffer.buffer_draw_top ?
			wall.start : buffer.buffer_draw_top;
	sv_draw.old_w = ray.w;
}
