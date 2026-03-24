/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	print_error(void)
{
	write(2, "Error\n", 6);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	simulation.forks = NULL;
	simulation.philosophers = NULL;
	simulation.philosopher_count = 0;
	if (parse_arguments(argc, argv, &simulation) != 0)
		return (print_error(), EXIT_FAILURE);
	if (init_simulation(&simulation) != 0)
		return (print_error(), EXIT_FAILURE);
	if (start_simulation(&simulation) != 0)
	{
		destroy_simulation(&simulation);
		return (print_error(), EXIT_FAILURE);
	}
	destroy_simulation(&simulation);
	return (EXIT_SUCCESS);
}
