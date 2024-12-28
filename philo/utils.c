/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:03:33 by paradari          #+#    #+#             */
/*   Updated: 2024/12/28 13:50:53 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_in_rules(t_rules *rules)
{
	if (rules->forks_lock != NULL)
		free(rules->forks_lock);
	if (rules->philo)
		free(rules->philo);
}

time_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

int	err_msg(char *msg, int ret)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write (2, msg, i);
	return (ret);
}

void	*err_null_ret(char *msg, t_rules *rules)
{
	printf("%s/n", msg);
	if (rules)
		ft_free_in_rules(rules);
	return (NULL);
}

