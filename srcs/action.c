/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:55 by pineau            #+#    #+#             */
/*   Updated: 2023/06/19 18:31:15 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_threads **philo)
{
	t_threads	*current;

	current = *philo;
	while (1)
	{
		if (eating(current) == 0)
			break ;
		if (thinking(current) == 0)
			break ;
		if (sleeping(current) == 0)
			break ;
	}
	printf("%d is dead\n", current->num);
}

long int	get_time(long time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - time;
	return (time);
}

int	eating(t_threads **philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	philo->last_eat = get_time(philo->last_eat);
	printf("%ld %d has taken a fork\n", \
		philo->last_eat - philo->time, philo->num);
	usleep(philo->tt_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

int	thinking(t_threads **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	usleep((philo->tt_die - (philo->tt_eat + philo->tt_sleep)) / 2);
	printf("%ld %d is thinking\n", \
		(time.tv_sec * 1000) + (time.tv_usec / 1000), philo->num);
}

int	sleeping(t_threads **philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	usleep(philo->tt_sleep);
	printf("%ld %d is sleeping\n", \
		(time.tv_sec * 1000) + (time.tv_usec / 1000), philo->num);
}
