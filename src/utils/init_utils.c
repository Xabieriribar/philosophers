#include "../../includes/philosophers.h"

// int print_philosophers_and_their_forks(t_simulation *simulation)
// {
//     int i = 0;
//     while (i < simulation->number_of_philosophers)
//     {
//         if (i == 0)
//         {
//             printf("<<< GENERAL INFORMATION >>>\n");
//             printf("Number of philosophers: %d\n", simulation->number_of_philosophers);
//             printf("Time to die: %d\n", simulation->time_to_die);
//             printf("Time to sleep: %d\n", simulation->time_to_sleep);
//             printf("Time to eat: %d\n", simulation->time_to_eat);
//             printf("Number of times each philosopher must eat: %d\n", simulation->number_of_times_each_philosopher_must_eat);
//         }
//         printf("Philosopher number %d\n", simulation->philosophers[i].philosopher_id);
//         printf("His left fork number is %d\n", simulation->philosophers[i].left_fork.index_for_debugging);
//         printf("His right fork number is %d\n", simulation->philosophers[i].right_fork.index_for_debugging);
//         i++;
//     }
//     return (0);
// }

int init_mutexes(t_simulation *simulation)
{
    int i;

    if (!simulation)
        return (1);
    i = 0;
    pthread_mutex_init(&(simulation->last_meal_mutex), NULL);
    pthread_mutex_init(&(simulation->stop_mutex), NULL);
    pthread_mutex_init(&(simulation->stdout_mutex), NULL);
    while (i < simulation->number_of_philosophers)
    {
        pthread_mutex_init(&(simulation->forks[i].mutex), NULL);
        simulation->forks[i].index_for_debugging = i;
        i++;
    }
    return (0);
}
int init_philosophers(t_simulation *simulation)
{
    int i;
    int philosopher_id;

    if (!simulation)
        return (1);
    i = 0;
    philosopher_id = 1;
    while (i < simulation->number_of_philosophers)
    {
        simulation->philosophers[i].philosopher_id = philosopher_id;
        if (i == 0)
            simulation->philosophers[i].left_fork = &simulation->forks[simulation->number_of_philosophers - 1];
        else
            simulation->philosophers[i].left_fork = &simulation->forks[i - 1];
        if (simulation->number_of_philosophers != 1)
            simulation->philosophers[i].right_fork = &simulation->forks[i];
        else
            simulation->philosophers[i].right_fork = NULL;
        simulation->philosophers->simulation_p = simulation;
        philosopher_id++;
        i++;
    }
    return (0);
}

int init_structs(t_simulation *simulation)
{
    simulation->philosophers = malloc(sizeof(struct s_philosopher ) * simulation->number_of_philosophers);
    if (!simulation->philosophers)
        return (1);
    simulation->forks = malloc(sizeof(struct s_fork ) * simulation->number_of_philosophers);
    if (!simulation->forks)
        return (1);
    if (init_mutexes(simulation) != 0)
        return (1);
    if (init_philosophers(simulation) != 0)
        return (1);
    // print_philosophers_and_their_forks(simulation);
    return (0);
}

