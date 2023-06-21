/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:05:20 by pineau            #+#    #+#             */
/*   Updated: 2023/06/21 14:40:09 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_suite(t_threads **philo)
{
	int			i;
	t_threads	*current;

	current = *philo;
	i = 0;
	while (i++ < current->philo)
		pthread_mutex_init(&current->fork, NULL);
}

void	init(char **argv)
{
	t_struct	*data;
	t_threads	*philo;

	data = malloc(sizeof(t_struct));
	if (!data)
		return ;
	data->philo = ft_atoi(argv[1]);
	data->fork = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->philo > 1024)
		return ;
	make_list(data, &philo);
	philo->philo = ft_atoi(argv[1]);
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	//philo->end = 0;
	init_suite(&philo);
	philosophers(data, &philo);
	end(data, philo);
}
