/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 00:00:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 00:00:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define PRINT_MESSAGE_DIE 1
# define PRINT_MESSAGE_EAT 2
# define IS_DEAD 3
# define PHILOSOPHER_ATE 4
# define READ_STOP_FLAG 5
# define LOCK_FORKS 6
# define UNLOCK_FORKS 7
# define PRINT_MESSAGE_FORK 8
# define PRINT_MESSAGE_SLEEP 9
# define PRINT_MESSAGE_THINK 10
# define ALL_PHILOSOPHERS_ATE 11
# define I_ATE 12
# define CHECK_IF_FULL 13

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				index_for_debugging;
}	t_fork;

typedef struct s_simulation	t_simulation;

typedef struct s_philosopher
{
	int				philosopher_id;
	long			last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_simulation	*simulation_p;
	int				meals_eaten;
	int				is_full;
	pthread_t		thread_handle;
}	t_philosopher;

typedef struct s_simulation
{
	long			number_of_philosophers;
	long			simulation_start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	int				stop;
	pthread_mutex_t	stdout_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_eaten_mutex;
	t_philosopher	*philosophers;
	t_fork			*forks;
}	t_simulation;

int		init_structs(t_simulation *simulation);
int		start_simulation(t_simulation *simulation);
int		is_dead(t_philosopher *philosopher);
int		is_even(int n);
long	set_time(void);
int		ft_usleep(long waiting_time, t_philosopher *philosopher);
int		set_simulation_time(t_simulation *simulation);
int		check_invalid_values(t_simulation *simulation);
int		contains_alphas(char **argv);
long	ft_atoi(const char *str);
int		ft_isalpha(int c);
int		check_last_meal_mutex(t_philosopher *philosopher, int mode);
void	check_fork_mutexes(t_philosopher *philosopher, int mode);
int		check_stop_mutex(t_simulation *simulation, int mode);
void	print_message(t_simulation *simulation, int message_type,
			int philosopher_id);
int		check_if_all_philosophers_ate(t_philosopher *philosopher, int flag);
void	*handle_one_thread(void *single_philosopher_struct);

#endif