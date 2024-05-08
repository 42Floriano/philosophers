/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:15:50 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 14:51:24 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Assigns forks to a philosopher in a way that 
 * prevents deadlock. 
 * Philosophers are assigned forks alternately 
 * to ensure that not all grab the left or right fork first.
 *
 * @param philo Pointer to the philosopher structure.
 * @param forks Array of forks available on the table.
 * @param pos The position of the philosopher at the table,
 * which dictates fork assignment.
 */
static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nb;

	philo_nb = philo->table->philo_nbr;
	philo->first_fork = &forks[(pos + 1) % philo_nb];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nb];
	}
	return ;
}

/**
 * Initializes all philosophers' data structures,
 * including setting initial values and assigning forks based on their position.
 *
 * @param table Pointer to the table structure that holds all simulation data.
 */

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_count = 0;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		philo->table = table;
		assign_forks(philo, table->forks, i);
		i++;
	}
	return ;
}

/**
 * Initializes all simulation data, including philosophers and forks. Allocates
 * memory and sets up mutexes for synchronization.
 *
 * @param table Pointer to the table structure to initialize.
 */
void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->table_mutex, NULL);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	return ;
}
