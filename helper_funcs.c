#include "minitalk.h"

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void	ft_putnbr(int n)
{
	long	nb;
	size_t	i;
	char	nbr[11];

	nb = n;
	if (nb == 0)
		write(1, "0", 1);
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	i = 0;
	while (nb)
	{
		nbr[i] = nb % 10 + 48;
		nb /= 10;
		i++;
	}
	while (i > 0)
		write(1, &nbr[--i], 1);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	min;

	n = 0;
	i = 0;
	min = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min++;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		n = n * 10 + str[i++] - 48;
	if (min == 1)
		return (-n);
	else
		return (n);
}