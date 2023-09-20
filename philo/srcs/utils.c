/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:12:50 by pineau            #+#    #+#             */
/*   Updated: 2023/09/20 16:52:31 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	a;

	a = 0;
	while ((s1[a] == s2[a]) && s1[a] != '\0' && s2[a] != '\0')
		a++;
	return (s1[a] - s2[a]);
}

void	check_death(t_threads *current, t_threads **philo)
{	
	while (1)
	{
		if (check_eat(philo) == 1)
		{
			pthread_mutex_lock(current->dead);
			*current->death = 1;
			pthread_mutex_unlock(current->dead);
			return ;
		}
		pthread_mutex_lock(current->lock);
		if (get_time(current->time) - current->last_eat >= current->tt_die)
		{
			pthread_mutex_lock(current->dead);
			*current->death = 1;
			pthread_mutex_unlock(current->dead);
			pthread_mutex_unlock(current->lock);
			mutex_printf(philo, 1);
			return ;
		}
		pthread_mutex_unlock(current->lock);
		current = current->next;
		usleep(50);
	}
}

int	check_eat(t_threads **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->philo)
	{
		pthread_mutex_lock((*philo)->lock);
		if ((*philo)->actual_eat < (*philo)->nbr_eat || (*philo)->nbr_eat == -1)
		{
			pthread_mutex_unlock((*philo)->lock);
			return (0);
		}
		pthread_mutex_unlock((*philo)->lock);
		(*philo) = (*philo)->next;
		i++;
	}
	(*philo) = (*philo)->prev;
	return (1);
}

void	eat_last_part(t_threads **philo)
{
	if ((*philo)->tt_eat > (*philo)->tt_die)
		usleep((*philo)->tt_die * 1000);
	else
		usleep((*philo)->tt_eat * 1000);
	pthread_mutex_unlock(&(*philo)->fork);
	pthread_mutex_unlock(&(*philo)->next->fork);
}
