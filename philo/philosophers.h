/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:03:12 by paradari          #+#    #+#             */
/*   Updated: 2024/12/29 01:28:46 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_rules
{
	int				nphilo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				nmeal;
	int				s_died;
	int				s_eat;
	long long		start_time;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	*forks_lock;
	struct s_philos	*philo;
}					t_rules;

typedef struct s_philos
{
	int				philo_nb;
	int				left_fork;
	int				right_fork;
	int				ate_times;
	long long		last_ate_time;
	pthread_t		id;
	struct s_rules	*rules;
}					t_philos;

int		ft_init_rules(t_rules *rules, char **av);
int		ft_init_mutex(t_rules *rules);

int		ft_start_sim(t_rules *rules);

// void	ft_is_dead_or_all_ate(t_rules *rules, t_philos *philo);
void	ft_end_sim(t_rules *rules, t_philos *philo);
void	ft_sleeping(long long sleeptime, t_rules *rules);
void	ft_writing(int id, char *str, t_rules *rules);


void	ft_free_in_rules(t_rules *rules);
time_t	get_time_in_ms(void);
int		ft_atoi(char *str);
int		err_msg(char *msg, int ret);
void    *err_null_ret(char *msg, t_rules *rules);

#endif
