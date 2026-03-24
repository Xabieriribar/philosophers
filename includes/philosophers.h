/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#             */
/*   Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ACT_FORK 1
# define ACT_EAT 2
# define ACT_SLEEP 3
# define ACT_THINK 4
# define ACT_DIED 5

typedef struct s_simulation	t_simulation;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	int				is_full;
	long			last_meal;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_simulation	*simulation;
}	t_philosopher;

typedef struct s_simulation
{
	int				philosopher_count;
	int				meals_required;
	int				stop;
	int				full_count;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_t		monitor;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	t_philosopher	*philosophers;
}	t_simulation;

int		parse_arguments(int argc, char **argv, t_simulation *simulation);
int		init_simulation(t_simulation *simulation);
int		start_simulation(t_simulation *simulation);
void	destroy_simulation(t_simulation *simulation);

long	ft_atol(const char *str);
int		is_strict_number(const char *str);

int		should_stop(t_simulation *simulation);
void	set_stop_flag(t_simulation *simulation);
long	get_last_meal(t_philosopher *philosopher);
void	mark_meal_done(t_philosopher *philosopher);
int		all_philosophers_full(t_simulation *simulation);

long	get_time_ms(void);
long	elapsed_time(t_simulation *simulation);
int		precise_sleep(t_simulation *simulation, long duration);
int		log_action(t_philosopher *philosopher, int action);

int		take_forks(t_philosopher *philosopher);
void	release_forks(t_philosopher *philosopher);
int		eat_cycle(t_philosopher *philosopher);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

#endif
