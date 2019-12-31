#include "ft_printf.h"

int		ft_print_ptg(t_data *data)
{
	char	*tab;
	char	chr;
	char	blank;
	int		chr_pos;

	chr = '%';
	blank = data->zero_flag && !data->minus_flag ? '0' : ' ';
	if(data->width <= 1)
	{
		tab = malloc(1);
		if (!tab)
			return (0);
		tab[0] = chr;
		data->pos++;
		return (ft_save(data, tab, 1));
	}
	tab = malloc(data->width);
	if (!tab)
		return (0);
	chr_pos = data->minus_flag ? 0 : data->width - 1;
	ft_memset(tab, blank, data->width);
	tab[chr_pos] = chr;
	data->pos++;
	return (ft_save(data, tab, data->width));
}

int		ft_print_num(t_data *data)
{
	int *p;

	p = va_arg(g_args, int *);
	if (!p)
		return (1);
	*p = data->size;
	return (1);
}

int		ft_print_err(t_data *data)
{
	int i;

	i = data->pos;
	while (data->str[i] != '%')
		i--;
	ft_save_chr(data, data->str[i]);
	data->pos = i + 1;
	return (1);
}