/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:09:09 by falberti          #+#    #+#             */
/*   Updated: 2024/04/30 14:13:12 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*donner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_thread(philo->talbe);
	while (!simulation_finished(philo->table))
	{
		// 1) am I full ?
		if (philo->full)
			break;
		// 2) eat
		eat(philo);	
		// 3) sleep
		
		// 4) think
		thinking(philo);
	}
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 0)
		;
	else
	{
		while (table->philo_nbr < i)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, NULL);
			i++;
		}
	}
	table->start_simulation = gettime(MILLISEOND);
	
	set_int(&table->table_mutex, &table->all_threads_ready, 1);

	i = 0;
	while (i < table->philo_nbr)
		pthread_join(&table->philo[i].thread_id, NULL);
	
	return ;
}