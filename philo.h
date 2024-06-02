#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_table
{
    int number_of_philosophers;
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t test;
} t_table;


void *philosopher(void *arg);
long ft_atol(char *str);
void parsing(int argc, char **argv, t_table *table);
int check_arg(char *arg);

#endif
