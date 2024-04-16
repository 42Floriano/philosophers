/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:15:50 by falberti          #+#    #+#             */
/*   Updated: 2024/04/16 14:04:02 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	
	return ;
}

static void philo_init(t_table *table)
{
	int	i;
	t_philo *philo;
	
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_count = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);

	}
	return ;
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr - 1);
	while (i < table->phili_nbr)
	{
		pthread_mutex_init(table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	return ;
}