#include "philo.h"

void    dead_philosopher(t_table *table, int id)
{
    pthread_mutex_lock(&table->test);
    if (table->number_of_times_each_philosopher_must_eat != 0)
    {
        table->number_of_times_each_philosopher_must_eat--;
        if (table->number_of_times_each_philosopher_must_eat == 0)
        {
            printf("Philosopher %d died\n", id);
            exit(1);
        }
    }
    pthread_mutex_unlock(&table->test);
}

void    get_forks(t_table *table, int id)
{
    pthread_mutex_lock(&table->forks[id - 1]);
    printf("Philosopher %d has taken a fork\n", id);
    pthread_mutex_lock(&table->forks[id % table->number_of_philosophers]);
    printf("Philosopher %d has taken a fork\n", id);
    printf("Philosopher %d is eating\n", id);
    usleep(table->time_to_eat * 1000);
    pthread_mutex_unlock(&table->forks[id - 1]);
    pthread_mutex_unlock(&table->forks[id % table->number_of_philosophers]);
    dead_philosopher(table, id);
}

void    *philosopher(void *arg)
{
    t_table *table;
    int id;

    table = (t_table *)arg;
    pthread_mutex_lock(&table->test);
    id = table->id;
    pthread_mutex_unlock(&table->test);
    while(1)
    {
        get_forks(table, id);
        sleeping(table, id);
        printf("Philosopher %d is thinking\n", id);
        
    }
    return (NULL);
}

void    creat_philosophers(t_table *table)
{
    int i;
    pthread_t *philosophers;

    i = 0;
    philosophers = malloc(sizeof(pthread_t) * table->number_of_philosophers);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
    pthread_mutex_init(&table->test, NULL);
    while (i < table->number_of_philosophers)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    i = 1;
    while (i <= table->number_of_philosophers)
    {
        table->id = i;
        pthread_create(&philosophers[i], NULL, (void *)philosopher, table);
        usleep(60);
        i++;
    }
    i = 0;
    while (i < table->number_of_philosophers)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
    free(philosophers);
    free(table->forks);
}

int main(int argc, char **argv)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (0);
    // table = (t_table){0, 0, 0, 0, 0};
    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    parsing(argc, argv, table);
    creat_philosophers(table);
    return (0);
}