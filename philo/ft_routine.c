/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:02 by kdanchal          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:05 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
		printf("%lu	%d is thinking\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	pthread_mutex_unlock(&philo->data->mutex_control);
	if (philo->data->time_to_eat >= philo->data->time_to_sleep)
	{
		if (philo->data->number_of_philosophers % 2 != 0)
			ft_usleep(philo->data->time_to_eat + philo->data->time_to_eat
				- philo->data->time_to_sleep);
		else
			ft_usleep(philo->data->time_to_eat - philo->data->time_to_sleep);
	}
	else
	{
		if (philo->data->number_of_philosophers % 2 != 0)
			ft_usleep(philo->data->time_to_eat + philo->data->time_to_eat
				- philo->data->time_to_sleep);
	}
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_control);
	if (philo->data->end_dinner == 0)
		printf("%lu	%d is sleeping\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
	pthread_mutex_unlock(&philo->data->mutex_control);
	ft_usleep(philo->data->time_to_sleep);
}

char	*ft_dinner_alone(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->data->mutex_control);
		printf("%lu	%d has taken a fork\n", ft_time_now_ms()
			- philo->data->time_start, philo->order);
		philo->data->end_dinner = 1;
		pthread_mutex_unlock(&philo->data->mutex_control);
		return ("Die alone");
	}
	else
	{
		return (NULL);
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (ft_dinner_alone(philo))
		return (NULL);
	if (philo->order % 2 != 0)
		ft_usleep(2);
	pthread_mutex_lock(&philo->data->mutex_control);
	while (philo->data->end_dinner == 0 && philo->one_full == 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_control);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		pthread_mutex_lock(&philo->data->mutex_control);
	}
	pthread_mutex_unlock(&philo->data->mutex_control);
	return (NULL);
}
