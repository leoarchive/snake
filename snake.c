/*
 *  Snake 
 *  Copyright (c) 2021 Leonardo Zamboni
 * 
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *  
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *  
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEIGHT 20
#define WIDTH 100

typedef struct matrix Matrix;

struct matrix
{
	uint16_t row;
	uint16_t col;
	uint8_t **v;
};

typedef struct list List;

struct list 
{
 	uint16_t x;
	uint16_t y;
	List *n;
	List *b;
};

List * 
create_list (void)
{
	List * l = (List *) malloc(sizeof(List));
	l->x = l->y = 0;
	l->n = l->b = NULL;
	return l;
}

void insert(List ** l, uint16_t x, uint16_t y)
{
	List * n = (List *) malloc(sizeof(List));
	n->x = x;
	n->y = y;
	(*l)->n = n;
	n->b = (*l);
	n->n = NULL;
	(*l) = n;
}

void 
set_snake_size(List **l, size_t size) 
{
	if (!(*l)) return;
	for (size_t i = 0; i < size; ++i)
	{
		(*l) = (*l)->b;
	}
	if ((*l)) (*l) = (*l)->b;
	while ((*l))
	{
		(*l) = (*l)->b;
		free((*l)->n);
		
	}
}

void
output_list (List *l)
{
	if (!l) return;
	printf("x: %d y: %d\n", l->x, l->y);
	output_list (l->b);
}

Matrix *
create_matrix (uint16_t row, uint16_t col)
{
	Matrix *m = (Matrix *)malloc (sizeof (Matrix));
	if (!m) exit (EXIT_FAILURE);
	m->row = row;
	m->col = col;
	m->v = (uint8_t **)malloc (row * sizeof (uint8_t *));
	for (size_t i = 0; i < row; ++i)
	{
		m->v[i] = (uint8_t *)calloc (col, sizeof (uint8_t));
	}
	return m;
}

void
output (Matrix *m)
{
    for (size_t i = 0; i < m->row; ++i)
        {
            for (size_t j = 0; j < m->col; ++j)
                {
			printf("%d", m->v[i][j]);
                }
	    puts("");
        }
}

void
set (Matrix **m, List * l)
{
	if (!l) return;
	(*m)->v[l->y][l->x] = 1;
	set (m,l->b);
}

int 
main(void) 
{
	Matrix *m = create_matrix (HEIGHT, WIDTH);
	List * l = create_list ();
	size_t x = 0;
	size_t y = 0;
	size_t s = 0;
	char k;

	while (1) 
	{
		k = getchar();

		switch (k) 
		{
			case 'a': x = x > 0 ? --x : WIDTH; break;
			case 's': y = y == HEIGHT ? 0 : ++y; break;
			case 'd': x = x == WIDTH ? 0 : ++x; break;
			case 'w': y = y > 0 ? --y : HEIGHT; break; 
			default: break;
		}
		set_snake_size(&l, s);
		system("clear");
		insert (&l, x, y);
		set (&m, l);
		output_list (l);
		output(m);
	}

	return 0;
}
