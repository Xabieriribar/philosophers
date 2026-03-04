#ifndef MINISHELL_H
# define MINISHELL_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef FAILED 1
#define FAILED 1

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_data;
// ==============================================================================
// UTILS
// ==============================================================================
int    ft_atoi(const char *str);
#endif 