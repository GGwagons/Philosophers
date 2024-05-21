/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:39:05 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/19 21:08:57 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init(t_philo *philo, t_data *data)
{
	size_t	i;

	i = 0;
	data->start = get_timestamp();
	while (i < data->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].finished = 0;
		philo[i].meals = 0;
		philo[i].okay = 0;
		philo[i].last_meal = data->start;
		if (philo->id % 2 == 0)
		{
			philo[i].right_fork = &data->forks[philo[i].id - 1];
			philo[i].left_fork = &data->forks[(philo[i].id)
				% data->num_of_philo];
		}
		else
		{
			philo[i].right_fork = &data->forks[(philo[i].id)
				% data->num_of_philo];
			philo[i].left_fork = &data->forks[philo[i].id - 1];
		}
		i++;
	}
}

void	ft_mutex_init(t_philo *philo, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead_philo, NULL);
}

void	ft_destroy(t_philo *philo, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo && philo[i].okay == 2)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_philo);
}

int	ft_makethread(t_philo *philo, t_data *data)
{
	pthread_t	create;
	pthread_t	thread[MAX_PHILO];
	size_t		i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].data = data;
		pthread_mutex_lock(&philo[i].philo_mutex);
		if (pthread_create(&thread[i], NULL, steps, &philo[i]) != 0)
		{
			philo[i].okay = 2;
			ft_destroy(philo, data);
			pthread_mutex_unlock(&philo[i].philo_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].philo_mutex);
		i++;
	}
	if (pthread_create(&create, NULL, monitoring_thread, philo) != 0)
		return (ft_destroy(philo, data), 1);
	pthread_join(create, NULL);
	thread_join(philo, data, thread);
	return (0);
}

int	thread_join(t_philo *philo, t_data *data, pthread_t *thread)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo && philo[i].okay != 2)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			ft_destroy(philo, data);
			return (1);
		}
		i++;
	}
	return (0);
}
