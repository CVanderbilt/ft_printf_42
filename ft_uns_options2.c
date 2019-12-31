#include "ft_printf.h"

char			*ft_check_prefix(t_data *data, char *str, char *prefix)
{
	if (!prefix)
		return (str);
	if (data->actual_type == 'o' && str[0] == '0')
		return (str);
	return (ft_arraynjoinfreeR(prefix, str, ft_strlen(prefix), ft_strlen(str) + 1));
}

char			*ft_check_prefix_mod(char *str)
{
	int i;
	int zero_pos;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '0' || ft_in_set("xX", str[i + 1]))
		return (str);
	zero_pos = i;
	while (str[i] == '0')
		i++;
	if (ft_in_set("xX", str[i]))
	{
		str[zero_pos + 1] = str[i];
		str[i] = '0';
	}
	return (str);
}

char				*ft_prefix_select(t_data *data, char type, unsigned long long int n)
{
	if (type == 'p')
		return (ft_strdup("0x"));
	if (data->hash_flag && ft_in_set("xX", type) && n != 0)
		return (type == 'x' ? ft_strdup("0x") : ft_strdup("0X"));
	if (data->hash_flag && type == 'o')
		return (ft_strdup("0"));
	return (0);
}