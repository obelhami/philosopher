#include "philo.h"

int    check_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '+' && i == 0 && arg[i + 1] >= '0' && arg[i + 1] <= '9')
            i++;
        if (arg[i] < '0' || arg[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void    fill_struct(t_table *table, long i, char *arg)
{
    table->nbr_limit_meals = -1;
    if (i == 1)
        table->nbr_philosophers = ft_atol(arg);
    if (i == 2)
        table->time_to_die = ft_atol(arg);
    if (i == 3)
        table->time_to_eat = ft_atol(arg);
    if (i == 4)
        table->time_to_sleep = ft_atol(arg);
    if (i == 5)
        table->nbr_limit_meals = ft_atol(arg); 
}
int    chack_int_max(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc - 1)
    {
        if (ft_atol(argv[i]) > 2147483647)
        {
            printf("Error: argument is too big\n");
            return (1);
        }
        i++;
    }
    i = 1;
    while (i < argc - 1)
    {
        if (ft_atol(argv[i]) < 0)
        {
            printf("Error: argument is negative\n");
            return (1);
        }
        i++;
    }
    return (0);
}

int    parsing(int argc, char **argv, t_table *table)
{
    long i;

    i = 1;
    if (chack_int_max(argc, argv))
        return (1);
    while (i < argc)
    {
        if (check_arg(argv[i]) == 0)
        {
            printf("Error: wrong argument\n");
            return (1);
        }
        fill_struct(table, i, argv[i]);
        i++;
    }
    return (0);
}