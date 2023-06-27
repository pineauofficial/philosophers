/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:05:20 by pineau            #+#    #+#             */
/*   Updated: 2023/06/27 18:30:20 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_threads	*init_suite(t_threads *philo)
{
	int					i;
	pthread_mutex_t		deadtmp;
	pthread_mutex_t		locktmp;

	pthread_mutex_init(&deadtmp, NULL);
	pthread_mutex_init(&locktmp, NULL);
	i = 0;
	while (i++ < (philo)->philo)
	{
		printf("philo num = %d\n", (philo)->num);
		pthread_mutex_init(&(philo)->fork, NULL);
		(philo)->dead = &deadtmp;
		(philo)->lock = &locktmp;
		(philo) = (philo)->next;
	}
	printf("philo actuel = %d\n", (philo)->num);
	return (philo);
}

void	init(char **argv)
{
	t_struct	*data;
	t_threads	*philo;
	int			i;

	data = malloc(sizeof(t_struct));
	if (!data)
		return ;
	data->philo = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->philo > 1024)
		return ;
	make_list(data, &philo);
	i = 0;
	while (i++ < data->philo)
	{
		philo->philo = ft_atoi(argv[1]);
		philo->tt_die = ft_atoi(argv[2]);
		philo->tt_eat = ft_atoi(argv[3]);
		philo->tt_sleep = ft_atoi(argv[4]);
		philo = philo->next;
	}
	philo = init_suite(philo);
	pthread_mutex_lock(philo->dead);
	pthread_mutex_unlock(philo->dead);
	exit(0);
	philosophers(data, &philo);
	end(data, philo);
}
