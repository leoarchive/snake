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

void
set_apple(Screen **m)
{
    (*m)->v[rand () % (HEIGHT - 1)][rand () % WIDTH] = 2;
}

_Bool
ate_yourself(Node * h, size_t x, size_t y)
{
    if (!h) return 0;
    if (x == h->x && y == h->y) return 1;
    return ate_yourself(h->next, x, y);
}

Snake *
create (size_t h, size_t w)
{
    Snake * s = malloc(sizeof(Snake));
    if (!s) exit (EXIT_FAILURE);
    s->s = s->x = s->y = 0;
    s->m = malloc(sizeof (List));
    if (!s->m) exit(EXIT_FAILURE);
    s->m->n = malloc(sizeof (Node));
    if (!s->m->n) exit(EXIT_FAILURE);
    s->m->head = s->m->n;
    s->m->n->next = NULL;
    s->m->n->x = s->m->n->y = 0;
    s->scn = malloc(sizeof (Screen));
    if (!s->scn) exit(EXIT_FAILURE);
    s->scn->row = h;
    s->scn->col = w;
    s->scn->v = malloc(h * sizeof(uint8_t *));
    if (!s->scn->v) exit (EXIT_FAILURE);
    for (size_t i = 0; i < h; ++i)
        {
            s->scn->v[i] = calloc(w, sizeof(uint8_t));
        }
    set_apple(&(s->scn));
    return s;
}

void set_cords (List **s, size_t x, size_t y)
{
    Node * n = malloc(sizeof(Node));
    n->x = x;
    n->y = y;
    n->next = (*s)->n;
    (*s)->head = n;
    (*s)->n = n;
}

void
screen (Screen *s)
{
    system("clear");
    for (size_t i = 0; i < s->row; ++i)
        {
            for (size_t j = 0; j < s->col; ++j)
                {
                    uint8_t aux = *(*(s->v + i) + j);
                    printf("%c", aux == 2 ? '*' : aux == 1 ? '.' : ' ');
                }
            puts("");
        }
}

void
bit_screen (Snake **s, Screen **m, Node * h)
{
    if (!h) return;
    if ((*m)->v[h->y][h->x] == 2)
        {
            (*s)->s++;
            set_apple(&(*m));
        }
    (*m)->v[h->y][h->x] = 1;
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

    while (1)
        {
            switch (getchar())
                {
                case 'a':
                    s->x = s->x == 0 ? WIDTH : s->x-1;
                    break;
                case 's':
                    s->y = s->y == HEIGHT-1 ? 0 : s->y+1;
                    break;
                case 'd':
                    s->x = s->x == WIDTH ? 0 : s->x+1;
                    break;
                case 'w':
                    s->y = s->y == 0 ? HEIGHT-1 : s->y-1;
                    break;
                default:
                    continue;
                }
            getchar();

            if (ate_yourself(s->m->head, s->x, s->y)) break;
            set_cords (&(s->m), s->x, s->y);
            snake_size (&(s->scn), &(s->m->head), s->s, 0);
            bit_screen (&s, &(s->scn), s->m->head);
            screen (s->scn);
        }

    return 0;
}
