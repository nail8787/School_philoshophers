int	ft_atoi(const char *str)
{
	int sign;
	int	value;

	value = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
	{
		str++;
	}
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += (*str - '0');
		str++;
	}
	return (value * sign);
}
