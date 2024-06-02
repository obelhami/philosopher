// #include <stdio.h>
#include "philo.h"

long ft_atol(char *str)
{
    long res;
    int sign;

    res = 0;
    sign = 1;
    while (*str == ' ')
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res * sign);
}