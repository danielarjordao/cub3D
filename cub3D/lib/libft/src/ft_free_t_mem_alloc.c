/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_mem_alloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:58 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/12 18:48:30 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_t_mem_alloc(t_mem_alloc *mem_allocation)
{
	if (mem_allocation->ptr_mem_list != NULL)
		ft_lstclear(&(mem_allocation->ptr_mem_list), free);
	if (mem_allocation->matrix_mem_list != NULL)
		ft_lstclear(&(mem_allocation->matrix_mem_list), ft_free_matrix);
}
