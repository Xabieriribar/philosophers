/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static const char	*action_name(int action)
{
	if (action == ACT_FORK)
		return ("has taken a fork");
	if (action == ACT_EAT)
		return ("is eating");
	if (action == ACT_SLEEP)
		return ("is sleeping");
	if (action == ACT_THINK)
		return ("is thinking");
	return ("died");
}

long	get_time_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
}

long	elapsed_time(t_simulation *simulation)
{
	return (get_time_ms() - simulation->start_time);
}

int	precise_sleep(t_simulation *simulation, long duration)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration)
	{
		if (should_stop(simulation))
			return (1);
		usleep(200);
	}
	return (0);
}

int	log_action(t_philosopher *philosopher, int action)
{
	int				print;
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	pthread_mutex_lock(&simulation->print_mutex);
	pthread_mutex_lock(&simulation->state_mutex);
	print = 0;
	if (action == ACT_DIED && !simulation->stop)
	{
		simulation->stop = 1;
		print = 1;
	}
	else if (action != ACT_DIED && !simulation->stop)
		print = 1;
	if (print)
	{
		printf("%ld %d %s\n", elapsed_time(simulation), philosopher->id,
			action_name(action));
		fflush(stdout);
	}
	pthread_mutex_unlock(&simulation->state_mutex);
	pthread_mutex_unlock(&simulation->print_mutex);
	return (!print);
}
