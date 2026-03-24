/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	stagger_start(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		precise_sleep(philosopher->simulation,
			philosopher->simulation->time_to_eat / 2);
}

long	think_delay(t_philosopher *philosopher)
{
	long	delay;

	if (philosopher->simulation->philosopher_count % 2 == 0)
		return (0);
	delay = philosopher->simulation->time_to_eat * 2
		- philosopher->simulation->time_to_sleep;
	if (delay <= 0)
		return (0);
	if (delay > philosopher->simulation->time_to_eat)
		return (philosopher->simulation->time_to_eat);
	return (delay);
}
