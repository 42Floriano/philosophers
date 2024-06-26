/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:09:09 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 14:34:34 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Simulates the thinking phase of a philosopher. 
 * Optionally logs the thinking status if it's
 * part of the simulation proper (not pre-simulation setup).
 *
 * @param philo Pointer to the philosopher's data structure.
 * @param pre_simulation Flag indicating if this is called 
 * before the main simulation starts.
 */
void	thinking(t_philo *philo, int pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_simulation == 0)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.22, philo->table);
}

/**
 * Runs the simulation for a single philosopher. 
 * It continuously checks if the simulation has ended,
 * allowing a lone philosopher to keep taking the fork and then sleeping, 
 * representing the inability to eat.
 *
 * @param data Pointer to the philosopher's data.
 * @return NULL indicating the thread completed its execution.
 */
void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

/**
 * Manages the eating phase of a philosopher, 
 * ensuring they pick up both forks before eating,
 * and releasing them afterwards. 
 * Also tracks meals and sets philosopher to full if meal count reaches limit.
 *
 * @param philo Pointer to the philosopher's data structure.
 */
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_count == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/**
 * The main function for each philosopher's thread in 
 * the dining philosophers simulation.
 * It controls the cycle of actions each philosopher takes
 *  — eating, sleeping, and thinking, and handles 
 * synchronization and checks for the completion of the simulation.
 *
 * @param data Pointer to the philosopher data structure.
 * @return NULL, indicating the thread completed its execution. 
 * This complies with the pthread_create API.
 */
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_synchro(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}

/**
 * Starts the dining simulation by initializing philosopher 
 * threads and a monitoring thread.
 * It handles the special case of a single philosopher 
 * as well as multiple philosophers,ensuring all threads
 *  are created and properly joined at the end of the simulation.
 *
 * @param table Pointer to the table structure containing
 *  all simulation data and configurations.
 */
void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		pthread_create(&table->philos[0].thread_id,
			NULL, lone_philo, &table->philos[0]);
	else
	{
		while (table->philo_nbr > i)
		{
			pthread_create(&table->philos[i].thread_id,
				NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	table->start_simulation = gettime(MILLISECOND);
	set_int(&table->table_mutex, &table->all_threads_ready, 1);
	i = -1;
	while (i++ < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_int(&table->table_mutex, &table->end_simulation, 1);
	pthread_join(table->monitor, NULL);
}
