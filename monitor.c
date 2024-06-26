/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:54 by falberti          #+#    #+#             */
/*   Updated: 2024/05/13 16:28:02 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Checks if a philosopher has died by comparing
 * the time elapsed since their last meal
 * to the time allowed before dying.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

/**
 * Continuously monitors all philosophers in 
 * the simulation to check if any have died.
 * If a philosopher has died, it sets 
 * the simulation to end and updates the status.
 *
 * @param data Pointer to the shared table data structure used in the simulation.
 * @return NULL after the function completes execution 
 * (conforms to pthreads requirements).
 */
void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
		i++;
	}
	return (NULL);
}
