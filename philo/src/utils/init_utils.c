/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	init_forks(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->philosopher_count)
	{
		if (pthread_mutex_init(&simulation->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&simulation->forks[i].mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	init_one_philo(t_simulation *simulation, int i)
{
	t_philosopher	*philosopher;
	int				left_index;

	philosopher = &simulation->philosophers[i];
	left_index = (i + simulation->philosopher_count - 1)
		% simulation->philosopher_count;
	philosopher->id = i + 1;
	philosopher->meals_eaten = 0;
	philosopher->is_full = 0;
	philosopher->last_meal = 0;
	philosopher->simulation = simulation;
	philosopher->right_fork = &simulation->forks[i];
	philosopher->left_fork = &simulation->forks[left_index];
}

static void	init_philosophers(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->philosopher_count)
	{
		init_one_philo(simulation, i);
		i++;
	}
}

int	init_simulation(t_simulation *simulation)
{
	simulation->forks = malloc(sizeof(t_fork) * simulation->philosopher_count);
	simulation->philosophers = malloc(sizeof(t_philosopher)
			* simulation->philosopher_count);
	if (!simulation->forks || !simulation->philosophers)
		return (free(simulation->forks), free(simulation->philosophers), 1);
	if (pthread_mutex_init(&simulation->state_mutex, NULL) != 0)
		return (free(simulation->forks), free(simulation->philosophers), 1);
	if (pthread_mutex_init(&simulation->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->state_mutex);
		return (free(simulation->forks), free(simulation->philosophers), 1);
	}
	if (init_forks(simulation) != 0)
		return (pthread_mutex_destroy(&simulation->state_mutex),
			pthread_mutex_destroy(&simulation->print_mutex),
			free(simulation->forks), free(simulation->philosophers), 1);
	init_philosophers(simulation);
	return (0);
}
