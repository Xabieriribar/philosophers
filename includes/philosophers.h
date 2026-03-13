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

#ifndef PRINT_MESSAGE_EAT
#define PRINT_MESSAGE_EAT 2
#endif 

#ifndef IS_DEAD
#define IS_DEAD 3
#endif 

#ifndef PHILOSOPHER_ATE
#define PHILOSOPHER_ATE 4
#endif 


#ifndef READ_STOP_FLAG
#define READ_STOP_FLAG 5
#endif 

#ifndef LOCK_FORKS
#define LOCK_FORKS 6
#endif 

#ifndef UNLOCK_FORKS
#define UNLOCK_FORKS 7
#endif 

#ifndef PRINT_MESSAGE_FORK
#define PRINT_MESSAGE_FORK 8
#endif 

#ifndef PRINT_MESSAGE_SLEEP
#define PRINT_MESSAGE_SLEEP 9
#endif

#ifndef PRINT_MESSAGE_THINK
#define PRINT_MESSAGE_THINK 10
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
    t_fork      *left_fork;
    t_fork      *right_fork;
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
    pthread_mutex_t last_meal_mutex; 
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
int     ft_usleep(int waiting_time, t_philosopher *philosopher);
int     set_simulation_time(t_simulation   *simulation);
// ==============================================================================
// PARSER UTILS
// ==============================================================================
int     check_invalid_values(t_simulation *simulation);
int     contains_alphas(char **argv);
int     ft_atoi(const char *str);
int     ft_isalpha(int c);

int     check_last_meal_mutex(t_philosopher *philosopher, int mode);
void    check_fork_mutexes(t_philosopher *philosopher, int mode);
int     check_stop_mutex(t_simulation *simulation, int mode);
void    print_message(t_simulation *simulation, int message_type, int philosopher_id);
#endif 