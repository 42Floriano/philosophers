/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:52:26 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 13:58:31 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * The main entry point of the philosophers simulation program. 
 * It initializes the simulation environment, 
 * starts the dining process, and cleans up resources afterward.
 *
 * @param ac Argument count.
 * @param av Argument vector, containing the command line arguments.
 * @return Returns 0 on successful completion of the program.
 */

/*
*  input ./ philo 5 		800 	200 	200 	[5]
* 				  n_philo	t_die	t_ear	t_sleep max_n_meal (optional) 
*/
int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong inpout:\n"
			G"Correct is ./ philo 5 800 200 200 [5]\n"RST);
	}
	return (0);
}
