/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:55:38 by falberti          #+#    #+#             */
/*   Updated: 2024/04/29 16:26:40 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(char *error)
{
	printf(RED"🚨 %s 🚨"RST, error);
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit('Gettimeofthedaz failed');
	if (time_code == SECOND)
		return (tv.tv_sec + (tv_tv_usec / 1000000));
	else if (time_code == MILLISEOND)
		return (tv.tv_sec + (tv_tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return (tv.tv_sec + tv_tv_usec);
	else 
		error_exit("Wring input to gettime!");
	return (122);
}
