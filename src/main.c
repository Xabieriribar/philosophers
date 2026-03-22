/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/03/22 12:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_simulation	*init_simulation(int argc, char **argv)
{
	t_simulation	*simulation;

	if (argc >= 7 || argc <= 4 || !argv || !*argv)
		return (NULL);
	if (contains_alphas(argv) != 0)
		return (NULL);
	simulation = malloc(sizeof(struct s_simulation));
	if (!simulation)
		return (NULL);
	simulation->number_of_philosophers = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	simulation->stop = 0;
	if (argv[5])
	{
		simulation->number_of_times_each_philosopher_must_eat
			= ft_atoi(argv[5]);
	}
	else
		simulation->number_of_times_each_philosopher_must_eat = -1;
	if (check_invalid_values(simulation) != 0)
		return (NULL);
	return (simulation);
}

int	main(int argc, char **argv)
{
	t_simulation	*simulation;

	simulation = init_simulation(argc, argv);
	if (!simulation)
	{
		printf("Invalid arguments. Usage: ./philo ");
		printf("number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (init_structs(simulation) != 0)
		return (printf("Failed to initialise them\n"), 1);
	if (start_simulation(simulation) != 0)
		return (printf("Failed to start simulation\n"), 1);
	printf("Managed to initialise them\n");
	return (0);
}
