/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:02:45 by miturk            #+#    #+#             */
/*   Updated: 2024/05/20 14:58:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_start(void *p)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = (t_philo *)p;
	if (philo->data->num_of_philo % 2 == 0)
	{
		if (philo->id % 2 != 0)
			ft_sleep (philo->data->time_to_eat, philo);
	}
	else if (philo->data->num_of_philo % 2 != 0)
	{
		if (philo->id == philo->data->num_of_philo
			&& philo->data->num_of_philo != 1)
			ft_sleep ((philo->data->time_to_eat * 2), philo);
		if (philo->id % 2 == 0)
			ft_sleep (philo->data->time_to_eat, philo);
	}
}

void	*steps(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo_start(p);
	pthread_mutex_lock(&philo->data->print);
	while (dead_flag(philo) == 0
		&& philo->meals < philo->data->num_meals)
	{
		pthread_mutex_unlock(&philo->data->print);
		philo_eat(philo);
		pthread_mutex_lock(&philo->data->print);
		if (philo->meals == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->data->dead_philo);
			philo->finished = 1;
			pthread_mutex_unlock(&philo->data->dead_philo);
			pthread_mutex_unlock(&philo->data->print);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->print);
		(philo_sleep(philo), philo_think(philo));
		pthread_mutex_lock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (p);
}

void	philo_sleep(t_philo *philo)
{
	ft_message("is sleeping", philo, philo->id);
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	ft_message("is thinking", philo, philo->id);
}
