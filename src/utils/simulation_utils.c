#include "../../includes/philosophers.h"

void    *start_monitoring_routine(void *void_simulation_struct)
{
    t_simulation    *simulation;
    int             i;

    simulation = (t_simulation *)void_simulation_struct;
    while (1)
    {
        i = 0;
        while (i < simulation->number_of_philosophers)
        {
            if (check_last_meal_mutex(&(simulation->philosophers[i]), IS_DEAD))
            {
                check_stop_mutex(simulation, IS_DEAD);
                usleep(10000);
                print_message(simulation, PRINT_MESSAGE_DIE, simulation->philosophers[i].philosopher_id);
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}

int     eat(t_philosopher *philosophers)
{
    if (philosophers->simulation_p->number_of_philosophers == 1)
    {
        pthread_mutex_lock(&(philosophers->left_fork->mutex));
        print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK, philosophers->philosopher_id);
        while (1)
        {
            if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
                return (1);
        }
    }
    if (is_even(philosophers->philosopher_id) != 0)
    {
        pthread_mutex_lock(&(philosophers->left_fork->mutex));
        print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK, philosophers->philosopher_id);
        pthread_mutex_lock(&(philosophers->right_fork->mutex));
        print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK, philosophers->philosopher_id);
        check_last_meal_mutex(philosophers, PHILOSOPHER_ATE);
        if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
            return (1);
        print_message(philosophers->simulation_p, PRINT_MESSAGE_EAT, philosophers->philosopher_id);
        if (ft_usleep(philosophers->simulation_p->time_to_eat, philosophers) != 0)
        {
            check_stop_mutex(philosophers->simulation_p, IS_DEAD);
            return (1);
        }
        pthread_mutex_unlock(&(philosophers->left_fork->mutex));
        pthread_mutex_unlock(&(philosophers->right_fork->mutex));
    }
    else
    {
        pthread_mutex_lock(&(philosophers->right_fork->mutex));
        print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK, philosophers->philosopher_id);
        pthread_mutex_lock(&(philosophers->left_fork->mutex));
        print_message(philosophers->simulation_p, PRINT_MESSAGE_FORK, philosophers->philosopher_id);
        check_last_meal_mutex(philosophers, PHILOSOPHER_ATE);
        if (check_stop_mutex(philosophers->simulation_p, READ_STOP_FLAG) != 0)
            return (1);
        print_message(philosophers->simulation_p, PRINT_MESSAGE_EAT, philosophers->philosopher_id);
        if (ft_usleep(philosophers->simulation_p->time_to_eat, philosophers) != 0)
        {
            check_stop_mutex(philosophers->simulation_p, IS_DEAD);
            return (1);
        }
        pthread_mutex_unlock(&(philosophers->right_fork->mutex));
        pthread_mutex_unlock(&(philosophers->left_fork->mutex));
    }
    return (0);
}

void    *start_philo_routine(void *void_philosopher_struct)
{
    t_philosopher *philosophers;

    philosophers = (t_philosopher *)void_philosopher_struct;
    if (eat(philosophers) != 0)
        return (NULL);
    return (NULL);
}


int start_simulation(t_simulation *simulation)
{
    int i;
    pthread_t       monitor_thread_handle;

    i = 0;
    set_simulation_time(simulation);
    while (i < simulation->number_of_philosophers)
    {
        pthread_create(&(simulation->philosophers[i].thread_handle), NULL, start_philo_routine, &(simulation->philosophers[i]));
        i++;
    }
    pthread_create(&monitor_thread_handle, NULL, start_monitoring_routine, simulation);
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        pthread_join(simulation->philosophers[i].thread_handle, NULL);
        i++;
    }
    pthread_join(monitor_thread_handle, NULL);
    return (0);

}