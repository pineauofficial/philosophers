/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/07/04 19:20:30 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_threads **philo)
{
	t_threads	*current;

	current = *philo;
	if (current->num % 2 == 0)
		thinking(&current);
	while (1)
	{
		if (eating_part2(&current) == 0)
			break ;
		if (sleeping(&current) == 0)
			break ;
		if (thinking(&current) == 0)
			break ;
	}
	if (*current->death == 1)
		return ;
}

void	solo_routine(t_threads **philo)
{
	pthread_mutex_lock(&(*philo)->fork);
	mutex_printf(philo, 2);
	usleep((*philo)->tt_die);
	pthread_mutex_unlock(&(*philo)->fork);
	return ;
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

void	philosophers(t_struct *data, t_threads **philo)
{
	int			i;
	int			ptc;
	t_threads	*current;

	current = *philo;
	set_time(data, philo);
	i = 0;
	if (current->philo == 1)
		ptc = pthread_create(&current->thread, NULL, (void *)solo_routine, current);
	else
	{
		while (i++ < data->philo)
		{
			ptc = pthread_create(&current->thread, NULL, (void *)routine, current);
			current = current->next;
			if (ptc != 0)
				return ;
		}
	}
	check_death(current, philo);
	if (threads_join(philo, data) == 0)
		return ;
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

void	end(t_struct *data, t_threads *philo, t_data *pointers)
{
	int			i;

	i = 0;
	while (i++ < philo->philo)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
	}
	free(data);
	free(pointers);
	free_list(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argc, argv);
	return (0);
}
