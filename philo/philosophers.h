/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/19 22:47:51 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define T_ERR "Error failed to create thread"
# define T_JOIN_ERR "Error failed to join thread"
# define M_ERR "Error failed to init mutex"
# define PHILO_ERR "Error philo must be between 1 and 200"
# define MALLOC_ERR "Error malloc failed"
# define ARGS_ERR "Error wrong arguments"

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
	long long		nb_eat;
	long long		last_eat;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs;
	pthread_mutex_t	death;
	int				death_flag;
	int				n_philo;
	long long		t_death;
	long long		t_eat;
	long long		t_sleep;
	long long		nb_eat;
	long long		start;
	t_philo			*philo;
}					t_rules;

// Routine
void				*ft_philo(void *args);
int					check_meal(t_rules *rules);
int					check_death(t_rules *rules, int i);
void				ft_death(t_rules *rules);
int					ft_thread(t_rules *rules);

// Actions
void				ft_logs(t_philo *philo, char *message);
void				take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
void				ft_eat(t_philo *philo);
int					my_meal(t_philo *philo);

// Init
int					init_rules(t_rules *rules, int ac, char **av);
int					init_philo(t_rules *rules);
int					init_mutex(t_rules *rules);

// Utils
long long			get_time(void);
long long			ft_atol(const char *nptr);
int					ft_free(t_rules *rules, char *msg, int mutex);
int					ft_args(int ac, char **av);
void				ft_usleep(long time);

#endif