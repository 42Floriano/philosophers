/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:52:26 by falberti          #+#    #+#             */
/*   Updated: 2024/05/06 14:25:39 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// check errors & fills table
		parse_input(&table, av);
		// init the data in the table
		data_init(&table);
		// start the dinner
		dinner_start(&table);
		// clean leaks if a philo dies or they are full
		clean(&table);
	}
	else
	{
		error_exit("Wrong inpout:\n"
			G"Correct is ./ philo 5 800 200 200 [5]\n"RST);
	}
	return (0);
}
