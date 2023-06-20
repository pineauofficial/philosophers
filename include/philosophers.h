/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pineau <pineau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:58:08 by pineau            #+#    #+#             */
/*   Updated: 2023/06/20 16:26:36 by pineau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_threads
{
	struct s_threads	*next;
	struct s_threads	*prev;
	int					num;
	pthread_t			thread;
	long int			last_eat;
	long int			time;
	int					philo;
	pthread_mutex_t		fork;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					death;
	int					end;
}	t_threads;

typedef struct s_struct
{
	int				philo;
	int				fork;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	pthread_mutex_t	mutex;
	struct timeval	start;
}	t_struct;

/*---------MANDATORY---------*/

/*main.c*/
void		routine(t_threads **philo);
void		philosophers(t_struct *data, t_threads **philo);
void		end(t_struct *data, t_threads *philo);
int			main(int argc, char **argv);

/*utils.c*/
int			ft_strcmp(char *s1, char *s2);

/*check_args.c*/
int			check_args(int argc, char **argv);
int			ft_atoi(const char *nptr);
int			sizestr(int n);
char		*ft_itoa(int n);
int			check_numbers(char **argv);

/*list_maker.c*/
void		circular(t_threads **philo);
void		make_list(t_struct *data, t_threads **philo);
void		*make_nod(int num);
void		add_nod(t_threads *head, t_threads *new);
void		free_list(t_threads *head);

/*action.c*/
long int	get_time(long time);
int			eating(t_threads **philo);
int			thinking(t_threads **philo);
int			sleeping(t_threads **philo);

/*threads.c*/
int			threads_join(t_threads **philo, t_struct *data);
void		set_time(t_struct *data, t_threads **philo);

/*init.c*/
void		init_suite(t_threads **philo);
void		init(char **argv);

#endif
