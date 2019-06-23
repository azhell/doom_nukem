/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:19:09 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/23 15:17:56 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_draw_floor(t_main *m, t_ray ray,
					t_heigth_wall wall, t_buffer *buf)
{
	static int32_t	w = -1;
	int32_t			save;
	t_rgb			col;
	double			x;

	save = wall.floor_h.start;
	x = ray.camdist - ray.addlen;
	col.r = 91;
	col.g = 26;
	col.b = 26;
	while (wall.floor_h.start < wall.floor_h.end
		&& wall.floor_h.start < buf->buffer_draw_bot)
	{
		col = ft_get_pixel_floor(m, ray, wall);
		ft_put_pixel_rgb(m, ray.w, wall.floor_h.start, col);
		wall.floor_h.start++;
	}
	w = ray.w;
	buf->buffer_draw_bot = save < buf->buffer_draw_bot ?
								save : buf->buffer_draw_bot;
}

void			ft_draw_wall(t_main *m, t_ray ray,
						t_heigth_wall wall, t_buffer *buf)
{
	t_iter		iter;
	int32_t		save;
	t_rgb		col;

	col.r = 255;
	col.g = 255;
	col.b = 255;
	iter.x = 0;
	iter.start = wall.start;
	while (iter.start < buf->buffer_draw_top)
	{
		iter.start++;
		iter.x++;
	}
	save = wall.start;
	while (iter.start < wall.end && iter.start < buf->buffer_draw_bot)
	{
		col = ft_get_pixel_wall(m, wall, iter.x, abs(wall.y));
		if (m->setting.fog == 1)
			col = ft_set_fog(col, ray);
		if (col.r >= 0)
			ft_put_pixel_rgb(m, ray.w, iter.start, col);
		iter.start++;
		iter.x++;
	}
	buf->buffer_draw_bot = save < buf->buffer_draw_bot ?
							save : buf->buffer_draw_bot;
}

void			ft_draw_cell(t_main *m, t_ray ray,
						t_heigth_wall wall, t_buffer *buf)
{
	int32_t		save;
	t_rgb		col;
	int32_t		x;

	x = 0;
	save = wall.ceil_h.start;
	while (wall.ceil_h.start < wall.ceil_h.end
			&& wall.ceil_h.start < buf->buffer_draw_bot)
	{
		col.r = 124;
		col.g = 75;
		col.b = 22;
		col = ft_get_pixel_ceil(m, ray, wall);
		ft_put_pixel_rgb(m, ray.w, wall.ceil_h.start, col);
		wall.ceil_h.start++;
		x++;
	}
	buf->buffer_draw_top = save > buf->buffer_draw_top ?
							save : buf->buffer_draw_top;
}

void			ft_draw_border(t_main *m, t_ray ray,
						t_heigth_wall wall, t_buffer *buf)
{
	int32_t		save;
	int32_t		color;
	int32_t		x;
	t_rgb		col;

	color = 0xFFFFFF;
	if (wall.border_bot.flag == 1)
	{
		x = 0;
		save = wall.border_bot.start;
		while (wall.border_bot.start < wall.border_bot.end &&
				wall.border_bot.start < buf->buffer_draw_bot)
		{
			col = ft_get_pixel_border(m, ray, wall, x, abs(wall.y));
			if (m->setting.fog == 1)
				col = ft_set_fog(col, ray);
			ft_put_pixel_rgb(m, ray.w, wall.border_bot.start, col);
			x++;
			wall.border_bot.start++;
		}
		buf->buffer_draw_bot = save < buf->buffer_draw_bot ?
								save : buf->buffer_draw_bot;
	}
	if (wall.border_top.flag == 1)
	{
		x = 0;
		while (wall.border_top.start < buf->buffer_draw_top)
		{
			wall.border_top.start++;
			x++;
		}
		save = wall.border_top.end;
		while (wall.border_top.start < wall.border_top.end &&
				wall.border_top.start < buf->buffer_draw_bot)
		{
			col = ft_get_pixel_border_top(m, ray, wall, x, abs(wall.y));
			if (m->setting.fog == 1)
				col = ft_set_fog(col, ray);
			ft_put_pixel_rgb(m, ray.w, wall.border_top.start, col);
			x++;
			wall.border_top.start++;
		}
		buf->buffer_draw_top = save > buf->buffer_draw_top ?
								save : buf->buffer_draw_top;
	}
}
