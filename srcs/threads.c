/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:28:25 by pineau            #+#    #+#             */
/*   Updated: 2023/06/27 17:37:31 by pineau           ###   ########.fr       */
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
	struct timeval	start;
	int				i;

	gettimeofday(&start, NULL);
	i = 0;
	while (i++ < data->philo)
	{
		(*philo)->time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
		(*philo) = (*philo)->next;
	}
	(*philo) = (*philo)->next;
}
