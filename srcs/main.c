/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/07/03 12:29:12 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_threads **philo)
{
	t_threads	*current;

	current = *philo;

	while (1)
	{
		if (eating(&current) == 0)
			break ;
		if (sleeping(&current) == 0)
			break ;
		if (thinking(&current) == 0)
			break ;
	}
	if (*current->death == 1)
		return ;
	*current->death = 1;
	mutex_printf(philo, 1);
}

void	philosophers(t_struct *data, t_threads **philo)
{
	int			i;
	int			ptc;
	t_threads	*current;

	current = *philo;
	set_time(data, philo);
	i = 0;
	while (i++ < data->philo)
	{
		ptc = pthread_create(&current->thread, NULL, (void *)routine, current);
		current = current->next;
		if (ptc != 0)
			return ;
	}
	if (threads_join(philo, data) == 0)
		return ;
}

void	end(t_struct *data, t_threads *philo, t_data *pointers)
{
	int			i;

	i = 0;
	while (i++ < philo->philo)
		pthread_mutex_destroy(&philo->fork);
	free(data);
	free(pointers);
	free_list(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argv);
	return (0);
}
