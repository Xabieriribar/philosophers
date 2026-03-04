#include "philosophers.h"

int init_data(t_data *data, int argc, char **argv)
{
    if (argc != 5 || argc != 6)
        return (FAILED);
    data = malloc(sizeof(struct s_data));
    if (!data)
        return (FAILED);
    data->number_of_philosophers = ft_atoi(argv[0]);
    data->time_to_die = ft_atoi(argv[1]);
    data->time_to_eat = ft_atoi(argv[2]);
    data->time_to_sleep = ft_atoi(argv[3]);
    if (argv[4])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[4]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
    
    return (0);
}
int main(int argc, char **argv)
{
    t_data  *data;

    if (init_data(data, argc, argv) == FAILED)
    parse_data(data);

}