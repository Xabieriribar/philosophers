#include "../../includes/philosophers.h"

void    *start_monitoring_routine(void *void_simulation_struct)
{
    t_simulation    *simulation;
    int             i;

    simulation = (t_simulation *)void_simulation_struct;
    while (1)
    {
        i = 0;
        if (is_dead(&(simulation->philosophers[i])))
            return (NULL);
        

        i++;
    
    }
}

int     eat(t_philosopher *philosophers)
{
    struct timeval time_struct;

    if (is_even(philosophers->philosopher_id) != 0)
    {
        pthread_mutex_lock(&(philosophers->left_fork));
        pthread_mutex_lock(&(philosophers->right_fork));
        gettimeofday(&time_struct, NULL);
        philosophers->last_meal = time_struct.tv_usec;
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
    // sleep(philosophers);
    // think(philosophers);
    // printf("Philosopher number %d\n", philosophers->philosopher_id);
    // printf("His left fork number is %d\n", philosophers->left_fork.index_for_debugging);
    // printf("His right fork number is %d\n", philosophers->right_fork.index_for_debugging);
    return (NULL);
}
int set_time(t_simulation   *simulation)
{
    struct timeval  time_struct;
    int             i;

    i = 0;
    gettimeofday(&time_struct, NULL);
    while (i < simulation->number_of_philosophers)
        simulation->philosophers[i++].last_meal = time_struct.tv_usec;
    simulation->simulation_start_time = time_struct.tv_usec; 
    return (0);
}
int start_simulation(t_simulation *simulation)
{
    int i;
    pthread_t       monitor_thread_handle;

    i = 0;
    set_time(simulation);
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