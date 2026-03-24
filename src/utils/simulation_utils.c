/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static void	assign_forks(t_philosopher *philosopher, t_fork **first,
	t_fork **second)
{
	if (philosopher->id % 2 == 0)
	{
		*first = philosopher->right_fork;
		*second = philosopher->left_fork;
	}
	else
	{
		*first = philosopher->left_fork;
		*second = philosopher->right_fork;
	}
}

static int	lock_one_fork(t_philosopher *philosopher, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (should_stop(philosopher->simulation))
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	if (log_action(philosopher, ACT_FORK) != 0)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	return (0);
}

int	take_forks(t_philosopher *philosopher)
{
	t_fork	*first;
	t_fork	*second;

	assign_forks(philosopher, &first, &second);
	if (lock_one_fork(philosopher, first) != 0)
		return (1);
	if (lock_one_fork(philosopher, second) != 0)
	{
		pthread_mutex_unlock(&first->mutex);
		return (1);
	}
	return (0);
}

void	release_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->left_fork->mutex);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
}

int	eat_cycle(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->simulation->state_mutex);
	philosopher->last_meal = get_time_ms();
	pthread_mutex_unlock(&philosopher->simulation->state_mutex);
	if (log_action(philosopher, ACT_EAT) != 0)
		return (release_forks(philosopher), 1);
	if (precise_sleep(philosopher->simulation,
			philosopher->simulation->time_to_eat) != 0)
		return (release_forks(philosopher), 1);
	mark_meal_done(philosopher);
	release_forks(philosopher);
	return (0);
}
