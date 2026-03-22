/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/03/22 12:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	is_dead(t_philosopher *philosopher)
{
	if (set_time() - philosopher->last_meal
		> philosopher->simulation_p->time_to_die)
		return (1);
	return (0);
}

int	is_even(int n)
{
	if (n % 2 != 0)
		return (1);
	return (0);
}

long	set_time(void)
{
	struct timeval	time_struct;

	gettimeofday(&time_struct, NULL);
	return ((time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000));
}

int	set_simulation_time(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosophers[i].last_meal = set_time();
		i++;
	}
	simulation->simulation_start_time = set_time();
	return (0);
}

int	ft_usleep(long waiting_time, t_philosopher *philosopher)
{
	long	time_before_loop;

	time_before_loop = set_time();
	while ((set_time() - time_before_loop) < waiting_time)
	{
		if (check_stop_mutex(philosopher->simulation_p, READ_STOP_FLAG))
			return (1);
		usleep(500);
	}
	return (0);
}
