/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:55 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 11:14:11 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage: 
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

# define DEBUG_MODE 1

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef struct s_table		t_table;
typedef pthread_mutex_t		t_mtx;

// ./ philo 5 800 200 200 [5]
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_count;
	int				full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_mtx			philo_mutex;
	t_table			*table;
}				t_philo;

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	int			end_simulation;
	int			all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_lock;
	t_fork		*forks;
	t_philo		*philos;
};

// Dinner
void	thinking(t_philo *philo, int pre_simulation);
void	dinner_start(t_table *table);

// Utils
void	error_exit(char *error);
void	*safe_malloc(size_t bytes);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

// Parsing
void	parse_input(t_table *table, char **av);

// Init 
void	data_init(t_table *table);

// Getters & Setters
void	set_int(t_mtx *mutex, int *dest, int value);
int		get_int(t_mtx *mutex, int *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
int		simulation_finished(t_table *table);

// Synchro Utils
void	wait_all_threads(t_table *table);
int		all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	de_synchro(t_philo *philo);

// Write
void	write_status(t_philo_status status, t_philo *philo, int debug);

// Monitor 
void	*monitor_dinner(void *data);
#endif