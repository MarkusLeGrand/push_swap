/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkantzer <lkantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:00:00 by vous              #+#    #+#             */
/*   Updated: 2025/01/21 17:53:21 by lkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/* 
** Petit utilitaire pour tri "classique" d'un tableau (bubble, insertion, ou quicksort).
** Ici, bubble sort pour la démo. 
** Pour 500 ou 1000 elements c'est suffisant. 
*/
static void bubble_sort(int *arr, int size)
{
	int i, j;
	int tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Récupère toutes les valeurs de A dans un tableau. */
static void fill_array_from_stack(t_stack *a, int *arr, int size)
{
	t_node	*cur;
	int		i;

	cur = a->head;
	i = 0;
	while (cur && i < size)
	{
		arr[i] = cur->value;
		cur = cur->next;
		i++;
	}
}

/* 
** Après avoir trié le tableau arr,
** pour chaque node dans A, on cherche la position (rang) de node->value dans arr.
** Puis on remplace node->value par ce rang (un entier de 0 à n-1).
*/
static void assign_ranks(t_stack *a, int *arr, int size)
{
	t_node	*cur;
	int		i;

	cur = a->head;
	while (cur)
	{
		/* Cherche la position de cur->value dans arr */
		i = 0;
		while (i < size)
		{
			if (arr[i] == cur->value)
			{
				cur->value = i; /* le rang */
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
}

/* 
** Compte le nombre de bits nécessaires pour représenter n (2^bits >= n).
*/
static int get_max_bits(int n)
{
	int bits = 0;
	while ((n >> bits) != 0)
		bits++;
	return bits;
}

/*
** Fonctions LSD :
** 1) On convertit les valeurs en rangs [0..n-1].
** 2) On fait max_bits passes : 
**    - Sur chaque bit, on parcourt A :
**      si le bit == 0 => pb, sinon => ra
**    - On rapatrie tout B dans A (pa).
*/
void	lsd_sort(t_stack *a, t_stack *b)
{
	int	size;
	int max_bits;
	int i, j;

	size = stack_size(a);
	if (size <= 1)
		return ;

	/* 1) On récupère les valeurs dans un tableau, on trie, on convertit en rang */
	int *arr = malloc(sizeof(int) * size);
	if (!arr)
		return ; /* ou exit(1) */
	fill_array_from_stack(a, arr, size);
	bubble_sort(arr, size);
	assign_ranks(a, arr, size);
	free(arr);

	/* 2) On détermine le nb de bits à examiner */
	max_bits = get_max_bits(size);

	/* 3) Passage bit par bit */
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			int top_rank = a->head->value;
			/* Si le bit i == 1 => on rotate, sinon => on push B */
			if (((top_rank >> i) & 1) == 1)
				ra(a);
			else
				pb(a, b);
			j++;
		}
		/* On ramène tout B dans A */
		while (stack_size(b) > 0)
			pa(a, b);
		i++;
	}
}
