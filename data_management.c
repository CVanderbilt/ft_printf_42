/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 13:50:32 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 13:51:40 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_save_chr(t_data *data, char c)
{
	char	*tmp;
	int		i;

	if (!(tmp = malloc(data->size + 1)))
		return (0);
	i = -1;
	while (++i < data->size)
		tmp[i] = data->out[i];
	tmp[i] = c;
	free(data->out);
	data->out = tmp;
	data->size++;
	return (1);
}

int		ft_save(t_data *data, char *tab, int size)
{
	char	*tab_aux;

	tab_aux = ft_arraynjoin(data->out, tab, data->size, size);
	if (!tab_aux)
		return (0);
	data->size += size;
	free(data->out);
	free(tab);
	data->out = tab_aux;
	return (1);
}

void	ft_data_init(t_data *data, const char *str)
{
	data->pos = 0;
	data->width = 0;
	data->size = 0;
	data->precision = -1;
	data->minus_flag = 0;
	data->plus_flag = 0;
	data->zero_flag = 0;
	data->l_flag = 0;
	data->h_flag = 0;
	data->blank_flag = 0;
	data->hash_flag = 0;
	data->actual_type = 0;
	data->set_flags = ft_strdup("-0+ #");
	data->set_types = ft_strdup("ucsdpxXilof%");
	data->out = ft_strdup("");
	data->str = ft_strdup(str);
}

void	ft_reinit_data(t_data *data)
{
	data->width = 0;
	data->precision = -1;
	data->minus_flag = 0;
	data->zero_flag = 0;
	data->plus_flag = 0;
	data->l_flag = 0;
	data->h_flag = 0;
	data->blank_flag = 0;
	data->hash_flag = 0;
	data->actual_type = 0;
}

void	ft_free_data(t_data *data)
{
	free(data->set_flags);
	free(data->set_types);
	free(data->out);
	free((void *)data->str);
}
