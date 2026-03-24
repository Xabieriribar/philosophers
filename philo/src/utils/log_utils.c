/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
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

static int	append_number(char *buffer, int index, long value)
{
	char	digits[20];
	int		count;

	if (value == 0)
		return (buffer[index] = '0', index + 1);
	count = 0;
	while (value > 0)
	{
		digits[count++] = '0' + (value % 10);
		value /= 10;
	}
	while (count > 0)
		buffer[index++] = digits[--count];
	return (index);
}

static int	append_text(char *buffer, int index, const char *text)
{
	while (*text)
		buffer[index++] = *text++;
	return (index);
}

void	write_log_action(t_simulation *simulation, t_philosopher *philosopher,
	int action)
{
	char	buffer[64];
	int		length;

	length = 0;
	length = append_number(buffer, length, elapsed_time(simulation));
	buffer[length++] = ' ';
	length = append_number(buffer, length, philosopher->id);
	buffer[length++] = ' ';
	length = append_text(buffer, length, action_name(action));
	buffer[length++] = '\n';
	write(1, buffer, length);
}
