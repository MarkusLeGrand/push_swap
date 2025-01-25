/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkantzer <lkantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:00:00 by vous              #+#    #+#             */
/*   Updated: 2025/01/21 17:57:22 by lkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
   Principe simplifié de "Turk sort" :
   -----------------------------------
   On veut A triée (du sommet -> plus petit, vers bas -> plus grand).
   1) Tant que A n’est pas vide :
      - Trouver le maximum de A.
      - Le faire remonter au top (via ra ou rra selon son index).
      - pb => on empile le max sur B (B sera décroissante : top = max).
   2) On push tout B -> A (pa...) => A se retrouve croissante.
*/

static int	find_index_of_max(t_stack *a, int size)
{
	int		i;
	int		idx_max;
	int		max;
	t_node	*cur;

	cur = a->head;
	i = 0;
	idx_max = 0;
	max = -2147483648; /* ou INT_MIN */
	while (cur)
	{
		if (cur->value > max)
		{
			max = cur->value;
			idx_max = i;
		}
		cur = cur->next;
		i++;
	}
	(void)size;
	return (idx_max);
}

void	turk_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	idx_max;
	int	half;
	int	i;

	size = stack_size(a);
	while (size > 0)
	{
		idx_max = find_index_of_max(a, size);
		half = size / 2;
		/* Décider s’il vaut mieux ra ou rra */
		if (idx_max <= half)
		{
			i = 0;
			while (i < idx_max)
			{
				ra(a);
				i++;
			}
		}
		else
		{
			i = idx_max;
			while (i < size)
			{
				rra(a);
				i++;
			}
		}
		pb(a, b);
		size--;
	}
	/* B est en ordre décroissant. On rapatrie vers A => A en ordre croissant. */
	while (stack_size(b) > 0)
		pa(a, b);
}
