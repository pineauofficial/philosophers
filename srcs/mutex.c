/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:52:27 by pineau            #+#    #+#             */
/*   Updated: 2023/07/04 18:37:57 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_death(t_threads **philo)
{
	pthread_mutex_lock((*philo)->dead);
	if ((*(*philo)->death) == 1)
	{
		pthread_mutex_unlock((*philo)->dead);
		return (0);
	}
	pthread_mutex_unlock((*philo)->dead);
	return (1);
}

void	mutex_printf(t_threads **philo, int mode)
{
	pthread_mutex_lock((*philo)->lock);
	if (mode == 1)
		printf("%ld %d is dead \xF0\x9F\x98\xB5\n", \
		get_time((*philo)->time), (*philo)->num);
	if (mode == 2 && !*(*philo)->death)
		printf("%ld %d has taken a fork \xF0\x9F\x8D\xB4\n", \
		get_time((*philo)->time), (*philo)->num);
	if (mode == 3 && !*(*philo)->death)
		printf("%ld %d is thinking \xF0\x9F\xA4\x94\n", \
		get_time((*philo)->time), (*philo)->num);
	if (mode == 4 && !*(*philo)->death)
		printf("%ld %d is sleeping \xF0\x9F\x98\xB4\n", \
		get_time((*philo)->time), (*philo)->num);
	if (mode == 5 && !*(*philo)->death)
		printf("%ld %d is eating \xF0\x9F\x8D\x94\n", \
		get_time((*philo)->time), (*philo)->num);
	pthread_mutex_unlock((*philo)->lock);

}
