/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	should_stop(t_simulation *simulation)
{
	int	stop;

	pthread_mutex_lock(&simulation->state_mutex);
	stop = simulation->stop;
	pthread_mutex_unlock(&simulation->state_mutex);
	return (stop);
}

void	set_stop_flag(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->stop = 1;
	pthread_mutex_unlock(&simulation->state_mutex);
}

long	get_last_meal(t_philosopher *philosopher)
{
	long	last_meal;

	pthread_mutex_lock(&philosopher->simulation->state_mutex);
	last_meal = philosopher->last_meal;
	pthread_mutex_unlock(&philosopher->simulation->state_mutex);
	return (last_meal);
}

void	mark_meal_done(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->simulation->state_mutex);
	philosopher->meals_eaten++;
	if (philosopher->simulation->meals_required > 0 && !philosopher->is_full
		&& philosopher->meals_eaten >= philosopher->simulation->meals_required)
	{
		philosopher->is_full = 1;
		philosopher->simulation->full_count++;
	}
	pthread_mutex_unlock(&philosopher->simulation->state_mutex);
}

int	all_philosophers_full(t_simulation *simulation)
{
	int	full;

	pthread_mutex_lock(&simulation->state_mutex);
	full = (simulation->meals_required > 0
			&& simulation->full_count == simulation->philosopher_count);
	pthread_mutex_unlock(&simulation->state_mutex);
	return (full);
}
