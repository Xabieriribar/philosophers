#ifndef MINISHELL_H
# define MINISHELL_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef NULL 
#define NULL 1
#endif

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int *thread_exit_status;
}   t_data;
// ==============================================================================
// UTILS
// ==============================================================================
int    ft_atoi(const char *str);
#endif 