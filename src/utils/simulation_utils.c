#include "../../includes/philosophers.h"

int is_even(int n)
{
    if (n % 2 != 0)
        return (1);
    return (0);
}

void    *start_philo_routine(void *void_philosopher_struct)
{
    t_philosopher *philosophers;

    philosophers = (t_philosopher *)void_philosopher_struct;
    if (is_even(philosophers->philosopher_id) != 0)
    {
        pthread_mutex_lock(&(philosophers->left_fork));
        pthread_mutex_lock(&(philosophers->right_fork));
        while (i < 5)
    }
    else
    {
        pthread_mutex_lock(&(philosophers->right_fork));
        pthread_mutex_lock(&(philosophers->left_fork));
    }
    printf("Philosopher number %d\n", philosophers->philosopher_id);
    printf("His left fork number is %d\n", philosophers->left_fork.index_for_debugging);
    printf("His right fork number is %d\n", philosophers->right_fork.index_for_debugging);
    return (NULL);
}
int start_simulation(t_simulation *simulation)
{
    int i;
    struct timeval time_struct;

    i = 0;
    gettimeofday(&time_struct, NULL);
    while (i < simulation->number_of_philosophers)
        simulation->philosophers[i++].last_meal = time_struct.tv_usec;
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        pthread_create(&(simulation->philosophers[i].thread_handle), NULL, start_philo_routine, &(simulation->philosophers[i]));
        pthread_detach(simulation->philosophers[i].thread_handle);
        i++;
    }
    return (0);

}