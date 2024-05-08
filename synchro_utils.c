/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:10:39 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 13:37:07 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Blocks until all threads are ready, indicated by 
 * a variable in the table structure.
 * Continuously checks a flag in a thread-safe manner using a mutex.
 *
 * @param table Pointer to the table structure 
 * containing shared data among threads.
 */
void	wait_all_threads(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

/**
 * Checks if all threads have been successfully started by comparing a counter
 * to the expected number of philosopher threads.
 *
 * @param mutex Pointer to a mutex to ensure thread-safe 
 * access to the threads counter.
 * @param threads Pointer to the counter of currently running threads.
 * @param philo_nbr Total number of philosopher threads expected to run.
 * @return 1 if all threads are running, 0 otherwise.
 */
int	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * Atomically increases a long integer value.
 * This operation is protected by a mutex to prevent race conditions.
 *
 * @param mutex Pointer to the mutex that protects the long integer.
 * @param value Pointer to the long integer to be increased.
 */
void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

/**
 * Introduces a delay or changes the state to thinking 
 * to desynchronize the philosophers' actions.
 * This is done to prevent deadlocks and ensure 
 * all philosophers can act without interference.
 *
 * @param philo Pointer to the philosopher structure 
 * containing the philosopher's data.
 */
void	de_synchro(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, 1);
	}
}
