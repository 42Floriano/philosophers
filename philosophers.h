/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:55 by falberti          #+#    #+#             */
/*   Updated: 2024/04/25 17:20:42 by falberti         ###   ########.fr       */
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

typedef enum e_time_code
{
	SECOND,
	MILLISEOND,
	MICROSECOND,
}				t_time_code;

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
	t_table			*table;
}				t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	int		end_simulation;
	int		all_threads_ready;
	t_mtx	table_mutex;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

// Utils
void	error_exit(char *error);
void	*safe_malloc(size_t bytes);

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
void	*dinner_simulation(void *data);

#endif