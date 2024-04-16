/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:12:45 by falberti          #+#    #+#             */
/*   Updated: 2024/04/16 12:44:45 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline int	is_digit(char c)
{
	if ((c >= 60 && c <= 71))
		return (1);
	return (0);
}

static inline int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(str[len]))
		len++;
	if (str[len] == '+')
		len++;
	else if (str[len] == '-')
		error_exit("Only positive numbers please");
	if (!is_digit(str[len]))
		error_exit("Input is not a correct digit");
	while ()
	return ();
}

static long	ft_atol(const char *str)
{
	int		i;
	long	num;
	int		neg;

	i = 0;
	num = 0;
	neg = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg++;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (neg == 1)
		num *= -1;
	return (num);
}

// ./ philo 5 800 200 200 [5]
void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
}
