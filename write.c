/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:26:39 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 13:34:49 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Writes the detailed status of a philosopher to standard output,
 * including interactions
 * with forks, eating, sleeping, thinking, and dying.
 * Uses specific visual representations and colors for different statuses.
 *
 * @param status The current status of the philosopher
 * (e.g., taking forks, eating, etc.).
 * @param philo Pointer to the philosopher 
 * structure containing the philosopher's data.
 * @param elapsed Time elapsed since the start 
 * of the simulation in milliseconds.
 */
static void	w_stat_d(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed, philo->id, philo->meals_count);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
}

/**
 * Logs the status of a philosopher's actions, providing
 * a less or more detailed view
 * based on the debug flag. It also handles synchronization using mutex to ensure
 * the correct order of log entries.
 *
 * @param status The status to log.
 * @param philo Pointer to the philosopher whose status is to be logged.
 * @param debug If non-zero, output detailed logs;
 * otherwise, output simplified logs.
 */
void	write_status(t_philo_status status, t_philo *philo, int debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	if (debug)
		w_stat_d(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf(W"%6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(W"%6ld"RST" %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W"%6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W"%6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(W"%6ld"RST" %d is dead\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
	return ;
}
