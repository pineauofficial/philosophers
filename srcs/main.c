/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:02:36 by pineau            #+#    #+#             */
/*   Updated: 2023/06/18 18:23:39 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(void *philoid)
{
	pthread_mutex_t	mutex;
	t_threads		*philo;
	long int		b;
	struct timeval	time;

	philo = (t_threads *)philoid;
	usleep(philo->tt_eat);
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&time, NULL);
	philo->last_eat = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	b = philo->time;
	printf("%d a manger au bout de %ld\n", philo->num, philo->last_eat - b);
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}

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

void	routine(t_struct *data, t_threads **philo)
{
	struct timeval	time;
	long int		actual;
	t_threads		*current;
	int				i;

	i = 0;
	gettimeofday(&time, NULL);
	actual = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (1)
	{
		current = *philo;
		while (current)
		{
			eat(current);
			if (current->last_eat - actual > data->tt_die)
				i = 1;
			current = current->next;
		}
		current = NULL;
		if (i == 1)
			break ;
	}
	printf("%d is dead\n", current->num);
}

void	philosophers(t_struct *data, t_threads **philo)
{
	int			i;
	int			ptc;
	t_threads	*current;

	set_time(data, philo);
	current = *philo;
	i = 0;
	while (i++ < data->philo)
	{
		ptc = pthread_create(&current->thread, NULL, (void *)eat, current);
		current = current->next;
		if (ptc != 0)
			return ;
	}
	routine(data, philo);
	if (threads_join(philo, data) == 0)
		return ;
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
	philo->fork = ft_atoi(argv[1]);
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	philosophers(data, &philo);
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
//foutre les fourchettes dans un mutex
//les faire manger et noter l'heure a laquelle ils ont manger
//les zigouiller si ils ont pas manger depuis tt_die
