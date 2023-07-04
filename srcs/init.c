/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:05:20 by pineau            #+#    #+#             */
/*   Updated: 2023/07/04 18:03:16 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*init_data(t_struct **data, char **argv)
{
	(*data) = malloc(sizeof(t_struct));
	if (!(*data))
		return (NULL);
	(*data)->philo = ft_atoi(argv[1]);
	(*data)->tt_die = ft_atoi(argv[2]);
	(*data)->tt_eat = ft_atoi(argv[3]);
	(*data)->tt_sleep = ft_atoi(argv[4]);
	return (NULL);
}

t_threads	*init_philo(int argc, t_threads *philo, t_struct *data, char **argv)
{
	int	i;

	i = 0;
	while (i++ < data->philo)
	{
		philo->philo = ft_atoi(argv[1]);
		philo->tt_die = ft_atoi(argv[2]);
		philo->tt_eat = ft_atoi(argv[3]);
		philo->tt_sleep = ft_atoi(argv[4]);
		philo->actual_eat = 0;
		if (argc == 6)
			philo->nbr_eat = ft_atoi(argv[5]);
		else
			philo->nbr_eat = -1;
		philo = philo->next;
	}
	return (philo);
}

void	*init_pointers(t_data **pointers, t_threads *philo)
{
	int	i;

	(*pointers) = malloc(sizeof(t_data));
	if (!(*pointers))
		return (NULL);
	pthread_mutex_init(&(*pointers)->deadtmp, NULL);
	pthread_mutex_init(&(*pointers)->locktmp, NULL);
	(*pointers)->end = 0;
	i = 0;
	while (i++ < (philo)->philo)
	{
		pthread_mutex_init(&(philo)->fork, NULL);
		philo->dead = &(*pointers)->deadtmp;
		philo->lock = &(*pointers)->locktmp;
		philo->death = &(*pointers)->end;
		philo = philo->next;
	}
	return (NULL);
}

void	init(int argc, char **argv)
{
	t_struct	*data;
	t_threads	*philo;
	t_data		*pointers;

	init_data(&data, argv);
	make_list(data, &philo);
	philo = init_philo(argc, philo, data, argv);
	init_pointers(&pointers, philo);
	philosophers(data, &philo);
	end(data, philo, pointers);
}
