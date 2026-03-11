#ifndef MINISHELL_H
# define MINISHELL_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#ifndef NULL 
#define NULL 1
#endif

#ifndef PRINT_MESSAGE_DIE
#define PRINT_MESSAGE_DIE 1
#endif 


typedef struct s_fork
{
    pthread_mutex_t mutex;
    int             index_for_debugging;
}   t_fork;

typedef struct s_philosopher
{
    int         philosopher_id;
    int         last_meal;
    t_fork      left_fork;
    t_fork      right_fork;
    struct s_simulation *simulation_p;
    pthread_t   thread_handle;

}   t_philosopher;
typedef struct s_simulation
{
    int number_of_philosophers;
    int simulation_start_time;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int stop;
    pthread_mutex_t stdout_mutex;
    pthread_mutex_t stop_mutex;
    t_philosopher   *philosophers;
    t_fork          *forks;
}   t_simulation;

// ==============================================================================
// UTILS
// ==============================================================================
int     init_structs(t_simulation *simulation);
int     start_simulation(t_simulation *simulation);
int     is_dead(t_philosopher *philosopher);
int     is_even(int n);
int     set_time();
// ==============================================================================
// PARSER UTILS
// ==============================================================================
int     check_invalid_values(t_simulation *simulation);
int     contains_alphas(char **argv);
int     ft_atoi(const char *str);
int     ft_isalpha(int c);

#endif 