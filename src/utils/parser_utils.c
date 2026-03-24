/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	is_strict_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	invalid_values(long count, long die, long eat, long sleep)
{
	if (count <= 0 || count > INT_MAX)
		return (1);
	if (die <= 0 || eat <= 0 || sleep <= 0)
		return (1);
	if (die > INT_MAX || eat > INT_MAX || sleep > INT_MAX)
		return (1);
	return (0);
}

static int	valid_arguments(int argc, char **argv)
{
	if (!is_strict_number(argv[1]) || !is_strict_number(argv[2]))
		return (0);
	if (!is_strict_number(argv[3]) || !is_strict_number(argv[4]))
		return (0);
	if (argc == 6 && !is_strict_number(argv[5]))
		return (0);
	return (1);
}

int	parse_arguments(int argc, char **argv, t_simulation *simulation)
{
	long	meals;

	if (argc != 5 && argc != 6)
		return (1);
	if (!valid_arguments(argc, argv))
		return (1);
	simulation->philosopher_count = (int)ft_atol(argv[1]);
	simulation->time_to_die = ft_atol(argv[2]);
	simulation->time_to_eat = ft_atol(argv[3]);
	simulation->time_to_sleep = ft_atol(argv[4]);
	simulation->meals_required = -1;
	meals = -1;
	if (argc == 6)
		meals = ft_atol(argv[5]);
	if (invalid_values(simulation->philosopher_count, simulation->time_to_die,
			simulation->time_to_eat, simulation->time_to_sleep)
		|| (argc == 6 && (meals <= 0 || meals > INT_MAX)))
		return (1);
	if (argc == 6)
		simulation->meals_required = (int)meals;
	simulation->stop = 0;
	simulation->full_count = 0;
	return (0);
}
