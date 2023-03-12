/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/12 11:07:19 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		t_id;
	pthread_mutex_t	n_eat;
	pthread_mutex_t	l_eat;
	int				l_fork;
	int				r_fork;
	int				id;
	int				nb_eat;
	long			last_eat;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	info;
	pthread_mutex_t	death;
	int				death_flag;
	int				n_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	int				nb_eat;
	long			start;
	t_philo			*philo;
}					t_rules;

// Routine
void				*ft_philo(void *args);
int					check_meal(t_rules *rules);
int					check_death(t_rules *rules, int i);
void				*ft_death(void *args);
void				ft_thread(t_rules *rules);

// Actions
void				logs(t_philo *philo, char *message);
void				take_forks(t_rules *rules, t_philo *philo);
void				release_forks(t_rules *rules, t_philo *philo);
void				ft_eat(t_rules *rules, t_philo *philo);

// Init
void				init_rules(t_rules *rules, int ac, char **av);
void				init_philo(t_rules *rules);

// Utils
long				get_time(void);
long				ft_atol(const char *nptr);
void				ft_free(t_rules *rules);
int					ft_args(int ac, char **av);
void				ft_usleep(long time);

#endif