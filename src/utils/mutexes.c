/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/03/22 12:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	check_last_meal_mutex(t_philosopher *philosopher, int mode)
{
	pthread_mutex_lock(&(philosopher->simulation_p->last_meal_mutex));
	if (mode == PHILOSOPHER_ATE)
		philosopher->last_meal = set_time();
	else if (mode == IS_DEAD)
	{
		if (is_dead(philosopher))
		{
			pthread_mutex_unlock(&(philosopher->simulation_p->last_meal_mutex));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philosopher->simulation_p->last_meal_mutex));
	return (0);
}

int	check_stop_mutex(t_simulation *simulation, int mode)
{
	pthread_mutex_lock(&(simulation->stop_mutex));
	if (mode == IS_DEAD)
		simulation->stop = 1;
	else if (mode == READ_STOP_FLAG)
	{
		if (simulation->stop)
		{
			pthread_mutex_unlock(&(simulation->stop_mutex));
			return (1);
		}
	}
	pthread_mutex_unlock(&(simulation->stop_mutex));
	return (0);
}

static int	check_full_philosophers(t_philosopher *philosopher)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philosopher->simulation_p->number_of_philosophers)
	{
		if (philosopher->simulation_p->philosophers[i].meals_eaten
			>= philosopher->simulation_p
			->number_of_times_each_philosopher_must_eat)
			philosopher->simulation_p->philosophers[i].is_full = 1;
		if (philosopher->simulation_p->philosophers[i].is_full)
			j++;
		i++;
	}
	if (j == philosopher->simulation_p->number_of_philosophers)
		return (1);
	return (0);
}

int	check_if_all_philosophers_ate(t_philosopher *philosopher, int flag)
{
	pthread_mutex_lock(&(philosopher->simulation_p->meals_eaten_mutex));
	if (flag == I_ATE)
		philosopher->meals_eaten++;
	else if (flag == CHECK_IF_FULL)
	{
		if (check_full_philosophers(philosopher))
		{
			pthread_mutex_unlock(
				&(philosopher->simulation_p->meals_eaten_mutex));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philosopher->simulation_p->meals_eaten_mutex));
	return (0);
}
