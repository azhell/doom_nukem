/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:16:38 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/23 15:18:11 by vrudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				main(void)
{
	t_main	*main;

	main = init_main();
	ft_init(main);
	ft_sdlinit(main);
	init_buttons(main);
	ft_load_shoot(main, -1);
	ft_load_reload_1(main, -1);
	ft_load_reload_2(main, 19);
	start_menu(main);
	ft_putnbr(main->difficulty);
	ft_sdlloop(main);
	SDL_Quit();
	TTF_Quit();
	return (0);
}
