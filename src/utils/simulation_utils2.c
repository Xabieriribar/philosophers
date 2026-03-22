/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/03/22 12:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*handle_one_thread(void *single_philosopher_struct)
{
	t_philosopher	*single_philosopher;

	single_philosopher = (t_philosopher *)single_philosopher_struct;
	pthread_mutex_lock(&(single_philosopher->left_fork->mutex));
	print_message(single_philosopher->simulation_p, PRINT_MESSAGE_FORK,
		single_philosopher->philosopher_id);
	while (1)
	{
		if (check_stop_mutex(single_philosopher->simulation_p,
				READ_STOP_FLAG) != 0)
		{
			pthread_mutex_unlock(&(single_philosopher->left_fork->mutex));
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

static void	print_status_message(t_simulation *simulation, int message_type,
	int philosopher_id)
{
	long	time;

	time = set_time() - simulation->simulation_start_time;
	if (message_type == PRINT_MESSAGE_EAT)
		printf("%ld %d is eating\n", time, philosopher_id);
	else if (message_type == PRINT_MESSAGE_FORK)
		printf("%ld %d has taken a fork\n", time, philosopher_id);
	else if (message_type == PRINT_MESSAGE_SLEEP)
		printf("%ld %d is sleeping\n", time, philosopher_id);
	else if (message_type == PRINT_MESSAGE_THINK)
		printf("%ld %d is thinking\n", time, philosopher_id);
}

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
