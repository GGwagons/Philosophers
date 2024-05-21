/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:39:05 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/20 14:59:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	acquire_forks(pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork, t_philo *philo)
{
	if (philo->data->num_of_philo % 2 != 0 && philo->data->num_of_philo != 1)
		ft_sleep(50, philo);
	pthread_mutex_lock(first_fork);
	ft_message("has taken a fork", philo, philo->id);
	if (first_fork == second_fork)
	{
		pthread_mutex_unlock(first_fork);
		ft_sleep(philo->data->time_to_die, philo);
		return ;
	}
	else
	{
		pthread_mutex_lock(second_fork);
		ft_message("has taken a fork", philo, philo->id);
	}
}

void	release_forks(pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0 && philo->data->num_of_philo != 1)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	acquire_forks(first_fork, second_fork, philo);
	if (philo->data->num_of_philo == 1)
	{
		ft_sleep(philo->data->time_to_die, philo);
		return ;
	}
	update_meal_info(philo);
	ft_message("is eating", philo, philo->id);
	ft_sleep(philo->data->time_to_eat, philo);
	release_forks(first_fork, second_fork);
}
