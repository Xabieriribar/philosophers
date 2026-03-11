#include "../../includes/philosophers.h"

int     is_dead(t_philosopher *philosopher)
{
    if (set_time() > philosopher->last_meal + philosopher->simulation_p->time_to_die)
        return (1);
    return (0);
}

int is_even(int n)
{
    if (n % 2 != 0)
        return (1);
    return (0);
}

int set_time()
{
    struct timeval  time_struct;

    gettimeofday(&time_struct, NULL);
    return (time_struct.tv_usec);
}

int set_simulation_time(t_simulation   *simulation)
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