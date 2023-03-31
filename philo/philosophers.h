/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/31 16:55:33 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define T_ERR "Error failed to create thread"
# define M_ERR "Error failed to init mutex"
# define PHILO_ERR "Error philo must be > 0"
# define MALLOC_ERR "Error malloc failed"
# define ARGS_ERR "Run like this : ./philo nb_philo t_die t_eat \
t_sleep [nb_time_must_eat]\nwith args > 0 and <= INT_MAX"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		t_id;
	pthread_mutex_t	eat_info;
	int				l_fork;
	int				r_fork;
	int				id;
	int				nb_eat;
	long long		last_eat;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs;
	pthread_mutex_t	flag;
	int				stop_flag;
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	long long		start;
	t_philo			*philo;
}					t_rules;

// Routine
void				*ft_philo(void *args);
int					check_meal(t_rules *rules);
int					check_death(t_rules *rules, int i);
void				*ft_death(void *args);
int					ft_thread(t_rules *rules);

// Actions
void				ft_logs(t_philo *philo, char *message);
int					take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
int					ft_eat(t_philo *philo);
// int					my_meal(t_philo *philo);

// Init
int					ft_args(int ac, char **av);
int					init_rules(t_rules *rules, int ac, char **av);
int					init_philo(t_rules *rules);
int					init_mutex(t_rules *rules);

// Utils
long long			get_time(void);
long long			ft_atol(const char *nptr);
int					ft_free(t_rules *rules, char *msg, int error, int index);
void				ft_usleep(long time);
size_t				ft_strlen(const char *s);

#endif