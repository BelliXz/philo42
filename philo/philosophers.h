/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:05:40 by kdanchal          #+#    #+#             */
/*   Updated: 2024/04/26 11:47:49 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"    // use red
# define GREEN "\033[0;32m"  // use green
# define YELLOW "\033[0;33m" // use yell
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m" // use pink
# define CYAN "\033[0;36m"    // use blue
# define GRAY "\033[0;37m"
# define LRED "\033[0;91m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				order;
	int				fork_left;
	int				fork_right;
	size_t			time_last_meal;
	int				time_wait;
	int				number_of_eat_now;
	int				one_full;
	pthread_t		th;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long long		number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		number_of_must_eat;
	size_t			time_start;
	int				end_dinner;
	// int				human_all_full;
	int				human_qty_full;
	struct s_philo	*philo;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_control;
}					t_data;

// main
char				*ft_god_look_full(t_data *data);
char				*ft_god_look_die(t_data *data);
char				*ft_check_end_dinner(t_data *data);
int					ft_error_exit(char *s, int exit_type);
// int				main(int argc, char **argv);

// ft_eat
char				*ft_philo_full(t_philo *philo);
void				ft_left_right(t_philo *philo);
void				ft_right_left(t_philo *philo);
void				ft_begin_eat_full_or_finish_eat_full(t_philo *philo);
void				ft_eat(t_philo *philo);

// ft_routine
void				ft_think(t_philo *philo);
void				ft_sleep(t_philo *philo);
char				*ft_dinner_alone(t_philo *philo);
void				*ft_routine(void *arg);

// ft_set_and_free
void				ft_join_and_free(t_data *data);
int					ft_set_2(t_data *data);
int					ft_set(t_data *data, char **argv);
char				*ft_check_input(int argc, char **argv);
// void				ft_print_status(t_philo *philo);

// t_utils
long long			ft_atoi(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_time_now_ms(void);
void				ft_usleep(size_t time);

#endif
