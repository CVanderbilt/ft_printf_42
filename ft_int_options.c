/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:09:40 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:20:06 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
				free(tab_aux);
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
