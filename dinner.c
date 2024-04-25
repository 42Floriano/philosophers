/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:09:09 by falberti          #+#    #+#             */
/*   Updated: 2024/04/25 15:42:22 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*donner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	
	wait_all_thread(philo->talbe);
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
	
	return ;
}