#include "ft_printf.h"

char	*ft_width_int(t_data *data, char *str)
{
	char	*ret;
	char	blank;
	int		str_start;
	int		blank_start;
	int		size;

	if (!(ret = malloc(data->width + 1)))
		return (0);
	ret[data->width] = 0;
	size = ft_strlen(str);
	blank = ' ';
	str_start = 0;
	blank_start = size;
	if (!data->minus_flag)
	{
		blank = data->zero_flag ? '0' : ' ';
		str_start = data->width - size;
		blank_start = 0;
	}
	ft_memset(ret + blank_start, blank, data->width - size);
	ft_memmove(ret + str_start, str, size);
	free (str);
	return (ret);
}

char	*ft_precision_int(t_data *data, char *str)
{
	char	*ret;
	int		len;

	len = ft_strlen(str);
	if (data->precision < len)
	{
		if (len == 1 && str[0] == '0' && data->precision >= 0)
		{
			free (str);
			return (ft_strdup(""));
		}
		else
			return (str);
	}
	ret = ft_calloc(data->precision + 1, 1);
	if (!ret)
		return (str);
	ret[data->precision] = 0;
	ft_memmove(ret + data->precision - len, str, len);
	free (str);
	return (ret);
}

char	*ft_check_sign(char *str)
{
	int		i;
	int		frst_dgt;
	int		sign_pos;
	char	tmp;

	i = 0;
	while (str[i] == ' ')
		i++;
	frst_dgt = i;
	while (str[i] == '0')
		i++;
	if (!str[i] || ft_isdigit(str[i]))
		return (str);
	if (str[i] == ' ' && (str[i + 1] == ' ' || !str[i + 1]))
		return (str);
	sign_pos = i;
	tmp = str[sign_pos];
	str[sign_pos] = str[frst_dgt];
	str[frst_dgt] = tmp;
	return (str);
}

char	*ft_print_int_aux(t_data *data, char **tab_aux)
{
	long long int	n;
	char			*tab;

	data->zero_flag = data->minus_flag ? 0 : data->zero_flag;
	n = va_arg(g_args, long long int);
	if (data->l_flag)
		n = data->l_flag == 1 ? (long int)n : n;
	else if (data->h_flag)
		n = data->h_flag == 1 ? (short)n : (signed char)n;
	else
		n = (int)n;
	if (n < 0)
		*tab_aux = ft_strdup("-");
	else if (data->plus_flag || data->blank_flag)
		*tab_aux = data->plus_flag ? ft_strdup("+") : ft_strdup(" ");
	else
		*tab_aux = ft_strdup("");
	n *= n < 0 ? -1 : 1;
	tab = ft_itoa(n);
	return (tab);	
}

char	*ft_print_int_aux2(t_data *data, char **tab_aux)
{
	char	*tab;
	int		precision;
	int		size;

	*tab_aux = 0;
	if (!(tab = ft_print_int_aux(data, tab_aux)))
		return (0);
	precision = data->precision;
	data->zero_flag = precision >= 0 ? 0 : data->zero_flag;
	tab = ft_precision_int(data, tab);
	if (!data->zero_flag)
		if (!(tab = ft_strjoinfree(*tab_aux, tab, 'B')))
			return (0);
	size = ft_strlen(tab);
	if (data->width > size)
		tab = ft_width_int(data, tab);
	return (tab);
}

char	*ft_print_int_aux3(t_data *data)
{
	int				size;
	char			*tab;
	char			*tab_aux;

	tab = ft_print_int_aux2(data, &tab_aux);
	if (data->zero_flag && tab)
	{
		size = ft_strlen(tab);
		if (data->width < size)
		{
			if (!(tab = ft_strjoinfree(tab_aux, tab, 'B')))
				return (0);
		}
		else
		{
			if (tab[0] == ' ' || (tab[0] == '0' && size > 1))
			{
				tab[0] = tab_aux[0] ? tab_aux[0] : tab[0];
				free (tab_aux);
			}
			else
				tab = ft_strjoinfree(tab_aux, tab, 'B');
		}
	}
	return (tab);
}

int		ft_print_int(t_data *data)
{
	int				size;
	char			*tab;

	if (!(tab = ft_print_int_aux3(data)))
		return (0);
	if (!(tab = ft_check_sign(tab)))
		return (0);
	size = ft_strlen(tab);
	data->pos++;
	return (ft_save(data, tab, size));
}