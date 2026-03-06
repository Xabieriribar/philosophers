#include "../includes/philosophers.h"

t_data *init_data(int argc, char **argv)
{
    t_data  *data;

    if (argc >= 7 || argc <= 4)
        return (NULL);
    data = malloc(sizeof(struct s_data));
    if (!data)
        return (NULL);
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
    return (data);
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
    t_data  *data;
    pthread_t   *n_of_threads;
    int     i;

    n_of_threads = NULL;
    i = 0;
    data = init_data(argc, argv);
    if (!data)
        return (printf("Data NULL to initialise\n"), EXIT_FAILURE);
    while (i < data->number_of_philosophers)
    {
        pthread_create(&n_of_threads[i], NULL, eat, "I do");
        pthread_join(n_of_threads[i], (void **)&(data->thread_exit_status[i]));
        i++;
    }
    return (0);
}
