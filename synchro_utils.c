/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:10:39 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 11:12:52 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

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

void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

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
