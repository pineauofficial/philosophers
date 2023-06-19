/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/19 18:20:37 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers(t_struct *data, t_threads **philo)
{
	int			i;
	int			ptc;
	t_threads	*current;

	set_time(data, philo);
	current = *philo;
	circular(philo);
	i = 0;
	exit(0);
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
	init_suite(&philo);
	philosophers(data, &philo);
	end(data, philo);
}

void	end(t_struct *data, t_threads *philo)
{
	int			i;

	i = 0;
	while (i++ < philo->philo)
		pthread_mutex_destroy(&philo->fork);
	free(data);
	free_list(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argv);
	return (0);
}
