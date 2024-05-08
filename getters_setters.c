/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:47:37 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 14:06:04 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Sets an integer value in a thread-safe manner.
 * This function locks a mutex before setting the value 
 * and unlocks it afterwards to ensure that the write operation
 * does not conflict with other concurrent operations.
 *
 * @param mutex Pointer to the mutex that protects the integer.
 * @param dest Pointer to the integer that will be set.
 * @param value The value to assign to the integer.
 */
void	set_int(t_mtx *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

// Same as previous
void	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/**
 * Retrieves an integer value in a thread-safe manner.
 * This function locks a mutex before reading the value 
 * and unlocks it afterwards to ensure that the read 
 * operation is not affected by other concurrent write operations.
 *
 * @param mutex Pointer to the mutex that protects the integer.
 * @param value Pointer to the integer to read.
 * @return The value of the integer.
 */
int	get_int(t_mtx *mutex, int *value)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

// Same as previous
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * Checks if the simulation has finished.
 * This is determined by a flag in the table structure 
 * which is checked in a thread-safe manner.
 *
 * @param table Pointer to the table structure that holds simulation status data.
 * @return 1 if the simulation has finished, 0 otherwise.
 */
int	simulation_finished(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end_simulation));
}
