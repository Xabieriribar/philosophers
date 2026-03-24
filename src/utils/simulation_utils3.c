#include "../../includes/philosophers.h"

static int	check_philo_state(t_simulation *simulation, int i)
{
	if (check_last_meal_mutex(&(simulation->philosophers[i]), IS_DEAD))
	{
		check_stop_mutex(simulation, IS_DEAD);
		print_message(simulation, PRINT_MESSAGE_DIE,
			simulation->philosophers[i].philosopher_id);
		return (1);
	}
	if (simulation->number_of_times_each_philosopher_must_eat != -1
		&& check_if_all_philosophers_ate(&(simulation->philosophers[i]),
			CHECK_IF_FULL))
	{
		print_message(simulation, ALL_PHILOSOPHERS_ATE, 0);
		return (1);
	}
	return (0);
}
void	*start_monitoring_routine(void *void_simulation_struct)
{
	t_simulation	*simulation;
	int				i;

	simulation = (t_simulation *)void_simulation_struct;
	while (1)
	{
		i = 0;
		while (i < simulation->number_of_philosophers)
		{
			if (check_philo_state(simulation, i))
				return (NULL);
			i++;
		}
		usleep(10000);
	}
	return (NULL);
}

static int	lock_second_fork(t_philosopher *philosophers,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(second);
	if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
	{
		pthread_mutex_unlock(first);
		return (pthread_mutex_unlock(second), 1);
	}
	print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK,
		philosophers->philosopher_id);
	return (0);
}

void	*start_philo_routine(void *void_philosopher_struct)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)void_philosopher_struct;
	while (!check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG))
	{
		if (eat(philosophers) != 0)
			break ;
		if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
			break ;
		print_message(philosophers->simulation_p, PRINT_MESSAGE_SLEEP,
			philosophers->philosopher_id);
		if (ft_usleep(philosophers->simulation_p->time_to_sleep,
				philosophers) != 0)
			break ;
		print_message(philosophers->simulation_p, PRINT_MESSAGE_THINK,
			philosophers->philosopher_id);
	}
	return (NULL);
}



int	eat(t_philosopher *philosophers)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	assign_forks(&first, &second, philosophers);
	if (lock_first_fork(philosophers, first))
		return (1);
	if (lock_second_fork(philosophers, first, second))
		return (1);
	if (finish_eating(philosophers, first, second))
		return (1);
	return (0);
}