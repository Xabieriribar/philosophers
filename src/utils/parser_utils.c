#include "../../includes/philosophers.h"

int     ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int    ft_isspace(int c)
{
    if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
        return (1);
    return (0);
}

int     check_invalid_values(t_simulation *simulation)
{
    if (simulation->number_of_philosophers <= 0 || simulation->time_to_die <= 0 || simulation->time_to_eat <= 0 || simulation->time_to_sleep <= 0)
        return (1);
    return (0);

}

int     contains_alphas(char **argv)
{
    int i;
    int j;

    i = 1;
    if (!argv || !*argv)
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (ft_isalpha(argv[i][j]) != 0)
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

long    ft_atoi(const char *str)
{
    long   result;
    long   sign;
    long   i;
    
    result = 0;
    sign = 1;
    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (str[i] == '+' && str[i + 1] != '-')
        i++;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] && str[i] >= 48 && str[i] <= 57)
    {
        result *= 10;
	result += str[i] - 48;
	i++;
    }
    result *= sign;
    return (result);
}