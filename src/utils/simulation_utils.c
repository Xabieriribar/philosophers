/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 00:00:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	print_message(t_simulation *simulation, int message_type,
	int philosopher_id)
{
	pthread_mutex_lock(&(simulation->stdout_mutex));
	if (message_type == PRINT_MESSAGE_DIE)
	{
		usleep(10000);
		printf("%ld %d died\n", set_time() - simulation->simulation_start_time,
			philosopher_id);
	}
	else if (!check_stop_mutex(simulation, READ_STOP_FLAG))
		print_status_message(simulation, message_type, philosopher_id);
	else
		check_stop_mutex(simulation, IS_DEAD);
	pthread_mutex_unlock(&(simulation->stdout_mutex));
}

int	start_simulation(t_simulation *simulation)
{
	int			i;
	pthread_t	monitor_thread_handle;

	i = 0;
	set_simulation_time(simulation);
	create_threads(simulation, i);
	pthread_create(&monitor_thread_handle, NULL,
		start_monitoring_routine, simulation);
	join_threads(simulation, monitor_thread_handle);
	return (0);
}

static int	finish_eating(t_philosopher *philosophers,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	check_last_meal_mutex(philosophers, PHILOSOPHER_ATE);
	print_message(philosophers->simulation_p, PRINT_MESSAGE_EAT,
		philosophers->philosopher_id);
	check_if_all_philosophers_ate(philosophers, I_ATE);
	if (ft_usleep(philosophers->simulation_p->time_to_eat, philosophers) != 0)
	{
		pthread_mutex_unlock(first);
		return (pthread_mutex_unlock(second), 1);
	}
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (0);
}

static void	join_threads(t_simulation *simulation, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		pthread_join(simulation->philosophers[i].thread_handle, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

static void	create_threads(t_simulation *simulation, int i)
{
	if (simulation->number_of_philosophers == 1)
		pthread_create(&(simulation->philosophers[i].thread_handle), NULL,
			handle_one_thread, &(simulation->philosophers[i]));
	else
	{
		while (i < simulation->number_of_philosophers)
		{
			pthread_create(&(simulation->philosophers[i].thread_handle), NULL,
				start_philo_routine, &(simulation->philosophers[i]));
			i++;
		}
	}
}