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

void	assign_forks(pthread_mutex_t **first, pthread_mutex_t **second,
	t_philosopher *philosophers)
{
	if (is_even(philosophers->philosopher_id) != 0)
	{
		*first = &(philosophers->left_fork->mutex);
		*second = &(philosophers->right_fork->mutex);
	}
	else
	{
		*first = &(philosophers->right_fork->mutex);
		*second = &(philosophers->left_fork->mutex);
	}
}


static int	lock_first_fork(t_philosopher *philosophers, pthread_mutex_t *first)
{
	pthread_mutex_lock(first);
	if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
		return (pthread_mutex_unlock(first), 1);
	print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK,
		philosophers->philosopher_id);
	return (0);
}

