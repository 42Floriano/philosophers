/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:15:50 by falberti          #+#    #+#             */
/*   Updated: 2024/04/30 14:26:04 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nb;

	philo_nb = philo->table->philo_nbr;
	philo->second_fork = &forks[(pos + 1) % philo_nb];
	philo->first_fork = &forks[pos];
	if (philo->id % 2)
	{
	philo->first_fork = &forks[pos];
	philo->second_fork = &forks[(pos + 1) % philo_nb];
	}
	return ;
}

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
		philo->table = table;
		assign_forks(philo, table->forks, i);
		i++;
	}
	return ;
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	return ;
}
