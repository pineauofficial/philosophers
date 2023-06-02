/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/02 16:22:12 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*print_hello(void *thread_id)
{
	long			tid;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	tid = (long)thread_id;
	pthread_mutex_lock(&mutex);
	printf("Hello from thread %ld\n", tid);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}

int	threads_join(t_struct *philo)
{
	int	ptj;
	int	i;

	i = 0;
	while (i < philo->philo)
	{
		ptj = pthread_join(philo->threads[i], NULL);
		i++;
		if (ptj != 0)
			return (0);
	}
	return (1);
}

void	philosophers(t_struct *philo)
{
	long		i;
	int			ptc;

	philo->threads = malloc(sizeof(pthread_t) * philo->philo);
	if (!philo->threads)
		return ;
	i = 0;
	while (i < philo->philo)
	{
		ptc = pthread_create(&philo->threads[i], NULL, print_hello, (void *)i);
		i++;
		if (ptc != 0)
			return ;
	}
	if (threads_join(philo) == 0)
		return ;
}

void	init(char **argv)
{
	t_struct	*philo;

	philo = malloc(sizeof(t_struct));
	if (!philo)
		return ;
	philo->philo = ft_atoi(argv[1]);
	philo->fork = ft_atoi(argv[1]);
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	philosophers(philo);
	free(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		return (0);
	init(argv);
}
