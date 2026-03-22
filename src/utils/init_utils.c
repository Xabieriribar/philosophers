/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/03/22 12:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	init_mutexes(t_simulation *simulation)
{
	int	i;

	if (!simulation)
		return (1);
	i = 0;
	pthread_mutex_init(&(simulation->last_meal_mutex), NULL);
	pthread_mutex_init(&(simulation->stop_mutex), NULL);
	pthread_mutex_init(&(simulation->stdout_mutex), NULL);
	pthread_mutex_init(&(simulation->meals_eaten_mutex), NULL);
	while (i < simulation->number_of_philosophers)
	{
		pthread_mutex_init(&(simulation->forks[i].mutex), NULL);
		simulation->forks[i].index_for_debugging = i;
		i++;
	}
	return (0);
}

int	init_philosophers(t_simulation *simulation)
{
	int	i;
	int	philosopher_id;

	i = 0;
	philosopher_id = 1;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosophers[i].philosopher_id = philosopher_id;
		if (i == 0)
		{
			simulation->philosophers[i].left_fork
				= &simulation->forks[simulation->number_of_philosophers - 1];
		}
		else
			simulation->philosophers[i].left_fork = &simulation->forks[i - 1];
		if (simulation->number_of_philosophers != 1)
			simulation->philosophers[i].right_fork = &simulation->forks[i];
		else
			simulation->philosophers[i].right_fork = NULL;
		simulation->philosophers[i].simulation_p = simulation;
		simulation->philosophers[i].meals_eaten = 0;
		philosopher_id++;
		i++;
	}
	return (0);
}

int	init_structs(t_simulation *simulation)
{
	simulation->philosophers = malloc(sizeof(struct s_philosopher)
			* simulation->number_of_philosophers);
	if (!simulation->philosophers)
		return (1);
	simulation->forks = malloc(sizeof(struct s_fork)
			* simulation->number_of_philosophers);
	if (!simulation->forks)
		return (free(simulation->philosophers), 1);
	if (init_mutexes(simulation) != 0)
		return (1);
	if (init_philosophers(simulation) != 0)
		return (1);
	return (0);
}
