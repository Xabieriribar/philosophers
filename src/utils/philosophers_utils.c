#include "../../includes/philosophers.h"

int init_structs(t_simulation *simulation)
{
    int     i;

    i = 0;
    simulation->philosophers = malloc(sizeof(struct s_philosopher *) * simulation->number_of_philosophers);
    if (!simulation->philosophers)
        return (1);
    simulation->forks = malloc(sizeof(struct s_fork *) * simulation->number_of_philosophers);
    simulation->philosophers[0].last_meal = 10;
    printf("%d", simulation->philosophers[0].last_meal);
    return (0);
}