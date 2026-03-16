#include "../../includes/philosophers.h"

int check_last_meal_mutex(t_philosopher *philosopher, int mode)
{
    pthread_mutex_lock(&(philosopher->simulation_p->last_meal_mutex));
    if (mode == PHILOSOPHER_ATE)
       philosopher->last_meal = set_time();
    else if (mode == IS_DEAD)
    {
        if (is_dead(philosopher))
        {
            pthread_mutex_unlock(&(philosopher->simulation_p->last_meal_mutex));
            return (1);
        }
    }
    pthread_mutex_unlock(&(philosopher->simulation_p->last_meal_mutex));
    return (0);
}

void    check_fork_mutexes(t_philosopher *philosopher, int mode)
{
    if (mode == LOCK_FORKS)
    {
        pthread_mutex_lock(&(philosopher->left_fork->mutex));
        pthread_mutex_lock(&(philosopher->right_fork->mutex));
    }
    else if (mode == UNLOCK_FORKS)
    {
        pthread_mutex_unlock(&(philosopher->left_fork->mutex));
        pthread_mutex_lock(&(philosopher->right_fork->mutex));
    }
}

int check_stop_mutex(t_simulation *simulation, int mode)
{
    pthread_mutex_lock(&(simulation->stop_mutex));
    if (mode == IS_DEAD)
        simulation->stop = 1;
    else if (mode == READ_STOP_FLAG)
    {
        if (simulation->stop)
        {
            pthread_mutex_unlock(&(simulation->stop_mutex));
            return (1);
        }
    }
    pthread_mutex_unlock(&(simulation->stop_mutex));
    return (0);
}

void    print_message(t_simulation *simulation, int message_type, int philosopher_id)
{
    pthread_mutex_lock(&(simulation->stdout_mutex));
    if (message_type == PRINT_MESSAGE_DIE)
        printf("%ld %d died\n", set_time() - simulation->simulation_start_time, philosopher_id);
    else if (message_type == PRINT_MESSAGE_EAT && !check_stop_mutex(simulation, READ_STOP_FLAG))
        printf("%ld %d is eating\n", set_time() - simulation->simulation_start_time, philosopher_id);
    else if (message_type == PRINT_MESSAGE_FORK && !check_stop_mutex(simulation, READ_STOP_FLAG))
        printf("%ld %d has taken a fork\n", set_time() - simulation->simulation_start_time, philosopher_id);
    else if (message_type == PRINT_MESSAGE_SLEEP && !check_stop_mutex(simulation, READ_STOP_FLAG))
        printf("%ld %d is sleeping\n", set_time() - simulation->simulation_start_time, philosopher_id);
    else if (message_type == PRINT_MESSAGE_THINK && !check_stop_mutex(simulation, READ_STOP_FLAG))
        printf("%ld %d is thinking\n", set_time() - simulation->simulation_start_time, philosopher_id);
    else
        check_stop_mutex(simulation, IS_DEAD);
    pthread_mutex_unlock(&(simulation->stdout_mutex));
}

int check_if_all_philosophers_ate(t_philosopher *philosopher, int flag)
{
    int i;
    int j;

    pthread_mutex_lock(&(philosopher->simulation_p->meals_eaten_mutex));
    j = 0;
    i = 0;
    if (flag == I_ATE)
        philosopher->meals_eaten++;
    else if (flag == CHECK_IF_FULL)
    {
        while (philosopher->simulation_p->philosophers[i].meals_eaten == philosopher->simulation_p->number_of_times_each_philosopher_must_eat && i < philosopher->simulation_p->number_of_philosophers)
            philosopher->simulation_p->philosophers[i++].is_full = 1;
        i = 0;
        while (i < philosopher->simulation_p->number_of_philosophers)
        {
            if (philosopher->simulation_p->philosophers[i].is_full)
                j++;
            if (j == philosopher->simulation_p->number_of_philosophers)
                return (pthread_mutex_unlock(&(philosopher->simulation_p->meals_eaten_mutex)), 1);
            i++;
        }
    }
    return (pthread_mutex_unlock(&(philosopher->simulation_p->meals_eaten_mutex)), 0);
}