/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:28:25 by pineau            #+#    #+#             */
/*   Updated: 2023/06/20 15:17:30 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	threads_join(t_threads **philo, t_struct *data)
{
	int			ptj;
	int			i;
	t_threads	*current;

	current = *philo;
	i = 0;
	while (i < data->philo)
	{
		ptj = pthread_join(current->thread, NULL);
		i++;
		if (ptj != 0)
			return (0);
		current = current->next;
	}
	return (1);
}

void	set_time(t_struct *data, t_threads **philo)
{
	t_threads		*current;
	struct timeval	start;
	int				i;

	current = *philo;
	gettimeofday(&start, NULL);
	i = 0;
	while (i++ < data->philo)
	{
		current->time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
		current = current->next;
	}
}
