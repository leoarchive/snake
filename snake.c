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
#include <time.h>

#define HEIGHT 20
#define WIDTH 100

typedef struct screen Screen;

struct screen
{
	size_t row;
	size_t col;
	uint8_t **v;
};

typedef struct node Node;

struct node 
{
 	size_t x;
	size_t y;
	Node *next;
};

typedef struct list List;

struct list
{
	Node *n;
	Node *head;
};

typedef struct snake Snake;

struct snake
{
	List *m;
	Screen *scn;
	size_t s;
	size_t x;
	size_t y;
};

Snake *
create (size_t h, size_t w)
{
	Snake * s = (Snake *) malloc(sizeof(Snake));
	if (!s) exit (EXIT_FAILURE);
	s->s = s->x = s->y = 0;
	s->m = (List *) malloc(sizeof (List));
	if (!s->m) exit(EXIT_FAILURE);
	s->m->n = (Node *) malloc(sizeof (Node));
	if (!s->m->n) exit(EXIT_FAILURE);
	s->m->head = s->m->n;
	s->m->n->next = NULL;
	s->m->n->x = s->m->n->y = 0;
	s->scn = (Screen *) malloc(sizeof (Screen));
	if (!s->scn) exit(EXIT_FAILURE);
	s->scn->row = h;
	s->scn->col = w;
	s->scn->v = (uint8_t **) malloc(h * sizeof(uint8_t *));
	if (!s->scn->v) exit (EXIT_FAILURE);
	for (size_t i = 0; i < h; ++i) 
	{
		s->scn->v[i] = (uint8_t *) calloc(w, sizeof(uint8_t));
	}	
	return s;
}

void set_cords (List **s, size_t x, size_t y) 
{
	Node * n = (Node *) malloc(sizeof(Node));
	n->x = x;
	n->y = y;
	n->next = (*s)->n;
	(*s)->head = n;
	(*s)->n = n;
}

void
scn (Screen *s)
{
    for (size_t i = 0; i < s->row; ++i)
        {
            for (size_t j = 0; j < s->col; ++j)
                {
			printf("%d", *(*(s->v + i) + j));
                }
	    puts("");
        }
}

void
set_apple(Screen **m) { (*m)->v[rand () % HEIGHT-1][rand () % WIDTH] = 2; }

void
bit_screen (Snake **s, Screen **m, Node * h)
{
	if (!h) return;
	if ((*m)->v[h->y][h->x] == 2) 
	{
		(*s)->s++;
	//	set_apple(&(*m));
	}
	if ((*m)->v[h->y][h->x] == 1) exit (EXIT_FAILURE); // death
	(*m)->v[h->y][h->x] = 1;
	bit_screen (s, m, h->next);
}

void
snake_size (Screen **m, Node **h, size_t s, size_t i)
{
	if (!(*(h))) return;
	if (i == s) 
	{
		Node *aux = (*h)->next;
		Node *tmp;
		while (aux) 
		{
			(*m)->v[aux->y][aux->x] = 0;	
			tmp = aux;
			aux = aux->next;
			free (tmp);
		}
		(*h)->next = NULL;
		return;
	};
	
	snake_size (&(*m), &(*h)->next, s, ++i);
}

int 
main(void) 
{ 
	srand(time(NULL));	
	Snake *s = create (HEIGHT, WIDTH);
	set_apple(&(s->scn));

	while (1) 
	{
		switch (getchar()) 
		{
			case 'a':
				s->x = s->x == 0 ? WIDTH : s->x-1; 
				break;
			case 's': 
				s->y = s->y == HEIGHT-1 ? 1 : s->y+1; 
				break;
			case 'd': 
				s->x = s->x == WIDTH ? 0 : s->x+1; 
				break;
			case 'w': 
				s->y = s->y == 0 ? HEIGHT-1 : s->y-1; 
				break; 			
			default: continue;
		}
		getchar();
	
		system("clear");
		set_cords (&(s->m), s->x, s->y);
		snake_size (&(s->scn), &(s->m->head), s->s, 0);
		bit_screen (&s, &(s->scn), s->m->head);
		scn (s->scn);
	}

	return 0;
}
