/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	create_threads(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->philosopher_count)
	{
		if (pthread_create(&simulation->philosophers[i].thread, NULL,
				philo_routine, &simulation->philosophers[i]) != 0)
			return (set_stop_flag(simulation), i);
		i++;
	}
	if (pthread_create(&simulation->monitor, NULL,
			monitor_routine, simulation) != 0)
		return (set_stop_flag(simulation), -1);
	return (simulation->philosopher_count);
}

static void	join_threads(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_simulation *simulation)
{
	int	i;
	int	count;

	simulation->start_time = get_time_ms();
	i = 0;
	while (i < simulation->philosopher_count)
	{
		simulation->philosophers[i].last_meal = simulation->start_time;
		i++;
	}
	count = create_threads(simulation);
	if (count == -1)
		return (join_threads(simulation, simulation->philosopher_count), 1);
	if (count != simulation->philosopher_count)
		return (join_threads(simulation, count), 1);
	join_threads(simulation, count);
	pthread_join(simulation->monitor, NULL);
	return (0);
}

void	destroy_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->philosopher_count)
	{
		pthread_mutex_destroy(&simulation->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->print_mutex);
	free(simulation->forks);
	free(simulation->philosophers);
}
