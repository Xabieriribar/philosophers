#include "../includes/philosophers.h"

t_simulation *init_simulation(int argc, char **argv)
{
    t_simulation  *simulation;

    if (argc >= 7 || argc <= 4 || !argv || !*argv)
        return (NULL);
    if (contains_alphas(argv) != 0)
        return (NULL);
    simulation = malloc(sizeof(struct s_simulation));
    if (!simulation)
        return (NULL);
    simulation->number_of_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        simulation->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        simulation->number_of_times_each_philosopher_must_eat = -1;
    if (check_invalid_values(simulation) != 0)
        return (NULL);
    return (simulation);
}
void    *eat(void *arg)
{
    char    *text;

    text = (char *)arg;
    printf("%s\n", text);
    return (NULL);
}
int main(int argc, char **argv)
{
    t_simulation      *simulation;
    int         i;

    i = 0;
    simulation = init_simulation(argc, argv);
    if (!simulation)
        return (printf("simulation NULL to initialise\n"), EXIT_FAILURE);
    if (init_structs(simulation) != 0)
        return (printf("Failed to initalise them\n"), 1);
    printf("Managed to initalise them\n");
    return (0);
}
