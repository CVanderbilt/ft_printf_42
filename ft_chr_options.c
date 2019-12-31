/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:01:51 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:04:52 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_width_str(t_data *data, char *str)
{
	int		len;
	int		blank_start;
	int		str_start;
	char	*ret;

	ret = malloc(data->width + 1);
	if (!ret)
		return (0);
	len = ft_strlen(str);
	if (!data->minus_flag)
	{
		blank_start = 0;
		str_start = data->width - len;
	}
	else
	{
		blank_start = len;
		str_start = 0;
	}
	ft_memmove(ret + str_start, str, len);
	ft_memset(ret + blank_start, ' ', data->width - len);
	ret[data->width] = 0;
	return (ret);
}

int		ft_print_str(t_data *data)
{
	char	*tab;
	char	*tmp;
	int		size;
	int		precision;

	tmp = va_arg(g_args, char *);
	if (!tmp)
		if (!(tmp = ft_strdup("(null)")))
			return (0);
	size = ft_strlen(tmp);
	precision = data->precision >= 0 ? data->precision : size;
	precision = precision > size ? size : precision;
	tab = ft_strndup(tmp, precision);
	if (!tab)
		return (0);
	if (precision >= data->width)
	{
		data->pos++;
		return (ft_save(data, tab, precision));
	}
	if (!(tmp = ft_width_str(data, tab)))
		return (0);
	free(tab);
	data->pos++;
	return (ft_save(data, tmp, ft_strlen(tmp)));
}

int		ft_print_chr(t_data *data)
{
	char			*tab;
	unsigned int	chr;
	int				chr_pos;

	chr = va_arg(g_args, unsigned int);
	if (data->width <= 1)
	{
		if (!(tab = malloc(1)))
			return (0);
		tab[0] = chr;
		data->pos++;
		return (ft_save(data, tab, 1));
	}
	if (!(tab = malloc(data->width)))
		return (0);
	chr_pos = data->minus_flag ? 0 : data->width - 1;
	ft_memset(tab, ' ', data->width);
	tab[chr_pos] = chr;
	data->pos++;
	return (ft_save(data, tab, data->width));
}
