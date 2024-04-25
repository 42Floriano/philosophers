/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:10:39 by falberti          #+#    #+#             */
/*   Updated: 2024/04/25 17:15:03 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_all_threads(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	wait_all_threads(philo->table);
	return (NULL);
}
