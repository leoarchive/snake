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

Matrix *
create (uint16_t row, uint16_t col)
{
	Matrix *m = (Matrix *)malloc (sizeof (Matrix));
	if (!m)
		exit (EXIT_FAILURE);
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
set (Matrix **m, size_t row, size_t col)
{
	(*m)->v[row][col] = 1;
}

int 
main(void) 
{
	Matrix *m = create(HEIGHT, WIDTH);
	size_t r = 0;
	size_t c = 0;
	char k;

	while (1) 
	{
		k = getchar();

		switch (k) 
		{
			case 'a': c = c > 0 ? --c : WIDTH - 1; break;
			case 's': r = r == HEIGHT - 1 ? 0 : ++r; break;
			case 'd': c = c == WIDTH - 1 ? 0 : ++c; break;
			case 'w': r = r > 0 ? --r : HEIGHT - 1; break; 
		}

		size_t aux;
		if ()


		for () 
		{
			system("clear");
			set(&m, r, c);
			output(m);
		}
	}

	return 0;
