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

unsigned long long	ft_mod_size_uns(t_data *data, unsigned long long int n)
{
	if (data->actual_type != 'p')
	{
		if (data->l_flag)
			n = data->l_flag == 1 ? (unsigned long int)n : n;
		else if (data->h_flag)
			n = data->h_flag == 1 ? (unsigned short)n : (unsigned char)n;
		else
			n = (unsigned int)n;
	}
	return (n);
}

char				*ft_translate(unsigned long long int n, char type)
{
	char *ret;

	if (type == 'u')
		ret = ft_itoa_unsigned(n, "0123456789");
	else if (type == 'x' || type == 'p')
		ret = ft_itoa_unsigned(n, "0123456789abcdef");
	else if (type == 'X')
		ret = ft_itoa_unsigned(n, "0123456789ABCDEF");
	else if (type == 'o')
		ret = ft_itoa_unsigned(n, "01234567");
	else
		ret = 0;
	return (ret);
}

char				*ft_print_uns_aux(t_data * data)
{
	unsigned long long int	n;
	int						precision;
	char					*tab;
	char					*prefix;

	data->actual_type = data->str[data->pos];
	n = ft_mod_size_uns(data, va_arg(g_args, unsigned long long int));
	prefix = ft_prefix_select(data, data->actual_type, n);
	if (!(tab = ft_translate(n, data->actual_type)))
		return (0);
	precision = data->precision;
	if (data->minus_flag)
		precision = data->precision > data->width ? precision : data->width;
	if (!(tab = ft_precision_int(data, tab)))
		return (0);
	tab = ft_check_prefix(data, tab, prefix);
	if (prefix)
		free(prefix);
	return (tab);
}

int					ft_print_uns(t_data *data)
{
	int						size;
	char					*tab;

	if (!(tab = ft_print_uns_aux(data)))
		return (0);
	size = ft_strlen(tab);
	if (data->width > size)
	{
		tab = ft_width_int(data, tab);
		size = ft_strlen(tab);
		if (!tab)
			return (0);
	}
	if (data->actual_type != 'o')
		tab = ft_check_prefix_mod(tab);
	data->pos++;
	return (ft_save(data, tab, size));
}