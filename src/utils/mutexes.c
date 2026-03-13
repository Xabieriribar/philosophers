#include "../../includes/philosophers.h"

int check_last_meal_mutex(t_philosopher *philosopher, int mode)
{
    int value;
    
    value = 0;
    pthread_mutex_lock(&(philosopher->simulation_p->last_meal_mutex));
    if (mode == PHILOSOPHER_ATE)
    {
       philosopher->last_meal = set_time();
    }
    else if (mode == IS_DEAD)
    {
        if (is_dead(philosopher))
            value = 1;
    }
    pthread_mutex_unlock(&(philosopher->simulation_p->last_meal_mutex));
    return (value);
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
        pthread_mutex_lock(&(philosopher->left_fork->mutex));
        pthread_mutex_lock(&(philosopher->right_fork->mutex));
    }
}

int check_stop_mutex(t_simulation *simulation, int mode)
{
    int return_value;

    return_value = 0;
    pthread_mutex_lock(&(simulation->stop_mutex));
    if (mode == IS_DEAD)
    {
        simulation->stop = 1;
    }
    else if (mode == READ_STOP_FLAG)
    {
        if (simulation->stop)
            return (1);
    }
    pthread_mutex_unlock(&(simulation->stop_mutex));
    return (return_value);
}

void    print_message(t_simulation *simulation, int message_type, int philosopher_id)
{
    pthread_mutex_lock(&(simulation->stdout_mutex));
    if (message_type == PRINT_MESSAGE_DIE)
    {
        printf("%d %d died\n", (set_time() - simulation->simulation_start_time) / 1000, philosopher_id);
    }
    else if (message_type == PRINT_MESSAGE_EAT)
        printf("%d %d is eating", (set_time() - simulation->simulation_start_time) / 1000, philosopher_id);
    else if (message_type == PRINT_MESSAGE_FORK)
        printf("%d %d has taken a fork\n", (set_time() - simulation->simulation_start_time) / 1000, philosopher_id);
    pthread_mutex_unlock(&(simulation->stdout_mutex));
}