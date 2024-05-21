/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:28 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/20 13:35:08 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring_thread(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (check_all_finished(philo) == 1 || check_any_dead(philo) == 1)
		{
			return (NULL);
		}
	}
	return (p);
}

int	dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_philo);
	if (philo->data->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_philo);
	return (0);
}

int	check_all_finished(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->dead_philo);
		pthread_mutex_lock(&philo[i].philo_mutex);
		if (philo[i].finished == 1)
			philo->data->finish_flag++;
		if (philo->data->finish_flag == philo->data->num_of_philo)
		{
			pthread_mutex_unlock(&philo[i].philo_mutex);
			pthread_mutex_unlock(&philo->data->dead_philo);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].philo_mutex);
		pthread_mutex_unlock(&philo->data->dead_philo);
		i++;
	}
	return (0);
}

int	check_any_dead(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->dead_philo);
		pthread_mutex_lock(&philo[i].philo_mutex);
		if ((get_timestamp() - philo[i].last_meal) >= philo->data->time_to_die)
		{
			philo->data->philo_is_dead = 1;
			ft_dead_msg("died", philo, philo[i].id);
			pthread_mutex_unlock(&philo[i].philo_mutex);
			pthread_mutex_unlock(&philo->data->dead_philo);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].philo_mutex);
		pthread_mutex_unlock(&philo->data->dead_philo);
		i++;
	}
	return (0);
}
