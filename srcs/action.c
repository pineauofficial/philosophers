/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:55 by pineau            #+#    #+#             */
/*   Updated: 2023/06/20 16:37:29 by pineau           ###   ########.fr       */
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
	pthread_mutex_lock(&(*philo)->fork);
	pthread_mutex_lock(&(*philo)->next->fork);
	(*philo)->last_eat = get_time((*philo)->last_eat);
	printf("%ld %d has taken a fork \xF0\x9F\x8D\xB4\n", \
		(*philo)->last_eat - (*philo)->time, (*philo)->num);
	usleep((*philo)->tt_eat);
	if (((*philo)->last_eat - (*philo)->time) > (*philo)->tt_die)
		return (0);
	pthread_mutex_unlock(&(*philo)->fork);
	pthread_mutex_unlock(&(*philo)->next->fork);
	return (1);
}

int	thinking(t_threads **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	usleep(((*philo)->tt_die - ((*philo)->tt_eat + (*philo)->tt_sleep)) / 2);
	printf("%ld %d is thinking \xF0\x9F\xA4\x94\n", \
		(time.tv_sec * 1000) + (time.tv_usec / 1000)
		- (*philo)->time, (*philo)->num);
	return (1);
}

int	sleeping(t_threads **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	usleep((*philo)->tt_sleep);
	printf("%ld %d is sleeping \xF0\x9F\x98\xB4\n", \
		(time.tv_sec * 1000) + (time.tv_usec / 1000)
		- (*philo)->time, (*philo)->num);
	if ((time.tv_sec * 1000) + (time.tv_usec / 1000) > (*philo)->tt_sleep)
		return (0);
	return (1);
}
