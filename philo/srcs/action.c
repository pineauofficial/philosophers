/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:55 by pineau            #+#    #+#             */
/*   Updated: 2023/09/20 18:46:22 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_part1_part1(t_threads **philo)
{
	if (mutex_death(philo) == 0)
		return (0);
	pthread_mutex_lock(&(*philo)->next->fork);
	mutex_printf(philo, 2);
	if (mutex_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo)->next->fork);
		return (0);
	}
	pthread_mutex_lock(&(*philo)->fork);
	mutex_printf(philo, 2);
	return (1);
}

int	eating_part1(t_threads **philo)
{
	if ((*philo)->num % 2 == 0)
	{
		if (!eating_part1_part1(philo))
			return (0);
	}
	else
	{
		if (mutex_death(philo) == 0)
			return (0);
		pthread_mutex_lock(&(*philo)->fork);
		mutex_printf(philo, 2);
		if (mutex_death(philo) == 0)
		{
			pthread_mutex_unlock(&(*philo)->fork);
			return (0);
		}
		pthread_mutex_lock(&(*philo)->next->fork);
		mutex_printf(philo, 2);
	}
	mutex_printf(philo, 5);
	return (1);
}

int	eating_part2(t_threads **philo)
{
	if (eating_part1(philo) == 0)
		return (0);
	pthread_mutex_lock((*philo)->lock);
	(*philo)->actual_eat++;
	pthread_mutex_unlock((*philo)->lock);
	if (mutex_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo)->next->fork);
		pthread_mutex_unlock(&(*philo)->fork);
		return (0);
	}
	pthread_mutex_lock((*philo)->lock);
	(*philo)->last_eat = get_time((*philo)->time);
	pthread_mutex_unlock((*philo)->lock);
	if (mutex_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo)->next->fork);
		pthread_mutex_unlock(&(*philo)->fork);
		return (0);
	}
	eat_last_part(philo);
	return (1);
}

int	sleeping(t_threads **philo)
{
	if (mutex_death(philo) == 0)
		return (0);
	mutex_printf(philo, 4);
	if ((*philo)->tt_eat + (*philo)->tt_sleep > (*philo)->tt_die)
		usleep(((*philo)->tt_die - (*philo)->tt_eat) * 1000);
	else
		usleep((*philo)->tt_sleep * 1000);
	return (1);
}

int	thinking(t_threads **philo)
{
	if (mutex_death(philo) == 0)
		return (0);
	mutex_printf(philo, 3);
	if ((*philo)->tt_eat > (*philo)->tt_die)
		usleep((*philo)->tt_die * 1000);
	else if ((*philo)->tt_sleep > (*philo)->tt_die)
		usleep(((*philo)->tt_die - (*philo)->tt_eat) * 1000);
	else if ((*philo)->tt_sleep + (*philo)->tt_eat > (*philo)->tt_die && \
		(*philo)->tt_sleep < (*philo)->tt_die && \
			(*philo)->tt_eat < (*philo)->tt_die)
		usleep((((*philo)->tt_die - \
		((*philo)->tt_eat + (*philo)->tt_sleep) / 2)) * 1000);
	else if ((*philo)->tt_sleep == (*philo)->tt_die && \
		(*philo)->tt_eat == (*philo)->tt_die)
		usleep((((*philo)->tt_die - \
		((*philo)->tt_eat + (*philo)->tt_sleep) / 2)) * 1000);
	else
		usleep((((*philo)->tt_die - \
		((*philo)->tt_eat + (*philo)->tt_sleep)) / 2) * 1000);
	return (1);
}
