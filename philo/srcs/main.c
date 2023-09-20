/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/09/18 13:16:37 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philosophers(t_struct *data, t_threads **philo)
{
	int			i;
	int			ptc;
	t_threads	*current;

	current = *philo;
	set_time(data, philo);
	i = 0;
	if (current->philo == 1)
		ptc = pthread_create(&current->thread, NULL, \
			(void *)solo_routine, current);
	else
	{
		while (i++ < data->philo)
		{
			ptc = pthread_create(&current->thread, NULL, \
				(void *)routine, current);
			current = current->next;
			if (ptc != 0)
				return ;
		}
	}
	check_death(current, philo);
	if (threads_join(philo, data) == 0)
		return ;
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
