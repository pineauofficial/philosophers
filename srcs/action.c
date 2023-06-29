/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:55 by pineau            #+#    #+#             */
/*   Updated: 2023/06/29 14:03:42 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(long timeuh)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	timeuh = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - timeuh;
	return (timeuh);
}

int	eating(t_threads **philo)
{
	if (mutex_death(philo) == 0)
		return (0);
	if ((*philo)->time - (*philo)->last_eat > (*philo)->tt_die)
		return (0);
	pthread_mutex_lock(&(*philo)->fork);
	if (mutex_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo)->fork);
		return (0);
	}
	mutex_printf(philo, 2);
	pthread_mutex_lock(&(*philo)->next->fork);
	if (mutex_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo)->next->fork);
		pthread_mutex_unlock(&(*philo)->fork);
		return (0);
	}
	(*philo)->last_eat = get_time((*philo)->time);
	mutex_printf(philo, 2);
	if ((*philo)->tt_eat > (*philo)->tt_die)
		usleep((*philo)->tt_die * 1000);
	else
		usleep((*philo)->tt_eat * 1000);
	pthread_mutex_unlock(&(*philo)->fork);
	pthread_mutex_unlock(&(*philo)->next->fork);
	return (1);
}

int	thinking(t_threads **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (mutex_death(philo) == 0)
		return (0);
	mutex_printf(philo, 3);
	usleep(((*philo)->tt_die - ((*philo)->tt_eat + (*philo)->tt_sleep))
		/ 2 * 1000);
	return (1);
}

int	sleeping(t_threads **philo)
{
	mutex_death(philo);
	mutex_printf(philo, 4);
	if ((*philo)->last_eat + (*philo)->tt_sleep > (*philo)->tt_die)
		usleep(((*philo)->tt_die - (*philo)->tt_eat) * 1000);
	else
		usleep((*philo)->tt_sleep * 1000);
	return (1);
}
