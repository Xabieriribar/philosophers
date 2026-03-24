/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	single_philo_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork->mutex);
	if (log_action(philosopher, ACT_FORK) == 0)
		precise_sleep(philosopher->simulation,
			philosopher->simulation->time_to_die + 1);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
	return (0);
}

static void	stagger_start(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		precise_sleep(philosopher->simulation,
			philosopher->simulation->time_to_eat / 2);
}

static int	philo_cycle(t_philosopher *philosopher)
{
	if (take_forks(philosopher) != 0)
		return (1);
	if (eat_cycle(philosopher) != 0)
		return (1);
	if (log_action(philosopher, ACT_SLEEP) != 0)
		return (1);
	if (precise_sleep(philosopher->simulation,
			philosopher->simulation->time_to_sleep) != 0)
		return (1);
	if (log_action(philosopher, ACT_THINK) != 0)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->simulation->philosopher_count == 1)
		return (single_philo_routine(philosopher), NULL);
	stagger_start(philosopher);
	while (should_stop(philosopher->simulation) == 0)
	{
		if (philo_cycle(philosopher) != 0)
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*simulation;
	int				i;

	simulation = (t_simulation *)arg;
	while (should_stop(simulation) == 0)
	{
		if (all_philosophers_full(simulation) != 0)
			return (set_stop_flag(simulation), NULL);
		i = 0;
		while (i < simulation->philosopher_count)
		{
			if (get_time_ms() - get_last_meal(&simulation->philosophers[i])
				>= simulation->time_to_die)
				return (log_action(&simulation->philosophers[i],
						ACT_DIED), NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
