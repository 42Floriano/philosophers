/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:55:38 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 13:32:21 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Displays an error message in red and exits the program with status code 1.
 * 
 * @param error_msg The error message to be displayed,
 * which describes the failure.
 */
void	error_exit(char *error_msg)
{
	printf(RED"🚨 %s 🚨"RST, error_msg);
	exit(1);
}

/**
 * Allocates memory of a specified size and checks for allocation failure.
 * If memory allocation fails, the program terminates with an error message.
 *
 * @param bytes The number of bytes to allocate.
 * @return A pointer to the allocated memory.
 */
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

/**
 * Retrieves the current time based 
 * on the specified format (seconds, milliseconds, or microseconds).
 * Handles errors in time retrieval and invalid format requests.
 *
 * @param time_code The format of the time to return.
 * @return The current time in the specified format or exits on error.
 */
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeoftheday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		error_exit("Wring input to gettime!");
	return (122);
}

/**
 * Implements a precise sleep function using microsecond intervals.
 * It continuously checks the elapsed time until the specified duration is met.
 *
 * @param usec The duration in microseconds 
 * for which the function should pause execution.
 * @param table Pointer to simulation-related data 
 * (used to check if the simulation has finished).
 */
void	precise_usleep(long usec, t_table *table)
{
	long		start;
	long		elapsed;
	long		rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 10000)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

/**
 * Cleans up resources at the end of a simulation. 
 * Destroys mutexes and frees allocated memory.
 *
 * @param table Pointer to the table structure containing 
 * all necessary simulation data.
 */
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (table->philo_nbr > i)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}
