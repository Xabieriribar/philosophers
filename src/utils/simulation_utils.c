#include "../../includes/philosophers.h"

void    print_message(t_simulation *simulation, int message_type, int philosopher_id)
{
    pthread_mutex_lock(&(simulation->stdout_mutex));
    if (message_type == PRINT_MESSAGE_DIE)
        printf("%d %d died", set_time(), philosopher_id);
    pthread_mutex_unlock(&(simulation->stdout_mutex));
}
void    *start_monitoring_routine(void *void_simulation_struct)
{
    t_simulation    *simulation;
    int             i;

    simulation = (t_simulation *)void_simulation_struct;
    while (1)
    {
        i = 0;
        if (is_dead(&(simulation->philosophers[i])))
        {
            print_message(simulation, PRINT_MESSAGE_DIE, simulation->philosopher_id);
            pthread_mutex_lock(&(simulation->stop_mutex));
            simulation->stop = 1;
            pthread_mutex_unlock(&(simulation->stop_mutex));
            return (NULL);

        }

        if ()
        i++;
    
    }
}

int     eat(t_philosopher *philosophers)
{
    if (is_even(philosophers->philosopher_id) != 0)
    {
        pthread_mutex_lock(&(philosophers->left_fork));
        pthread_mutex_lock(&(philosophers->right_fork));
        philosophers->last_meal = set_time();
        usleep(philosophers->simulation_p->time_to_sleep);
    }
    else
    {
        pthread_mutex_lock(&(philosophers->right_fork));
        pthread_mutex_lock(&(philosophers->left_fork));
    }
    return (0);
}

void    *start_philo_routine(void *void_philosopher_struct)
{
    t_philosopher *philosophers;

    philosophers = (t_philosopher *)void_philosopher_struct;
    eat(philosophers);
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
    pthread_create(&monitor_thread_handle, NULL, start_monitoring_routine, &simulation);
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        pthread_join(&simulation->philosophers[i].thread_handle, NULL);
        i++;
    }
    pthread_join(monitor_thread_handle, NULL);
    return (0);

}