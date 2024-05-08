/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertini <albertini@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:12:45 by falberti          #+#    #+#             */
/*   Updated: 2024/05/08 13:59:00 by albertini        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Checks if a character is a decimal digit.
 *
 * @param c The character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
static inline int	is_digit(char c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

/**
 * Checks if a character is a whitespace character.
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace, 0 otherwise.
 */
static inline int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/**
 * Validates and locates the starting point of a positive integer in a string,
 * skipping leading whitespaces and optional plus sign.
 *
 * @param str The input string containing the number.
 * @return Pointer to the start of the valid number within the string.
 */
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only positive numbers please");
	if (is_digit(*str) == 0)
		error_exit("Input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

/**
 * Converts a string to a long integer, ensuring the string contains a valid
 * positive integer formatted correctly.
 *
 * @param str The string to convert.
 * @return The numeric value of the string as a long integer.
 */
static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}

/**
 * Parses input arguments into simulation settings, converting time values from
 * milliseconds to microseconds for higher precision in timing functions.
 *
 * @param table Pointer to the structure holding all settings for the simulation.
 * @param av The array of command line arguments.
 */

/*
*  input ./ philo 5 		800 	200 	200 	[5]
* 				  n_philo	t_die	t_ear	t_sleep max_n_meal (optional) 
*/
void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("All timestamps must be greater than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	return ;
}
