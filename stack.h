/* See LICENSE file for copyright and license details. */

#ifndef STACK_H
#define STACK_H

struct node_float {
	float data;
	struct node_float *next;
};

struct node_char {
	char data;
	struct node_char *next;
};

/* Push float onto stack */
void push_float(struct node_float **head, float data);

/* Pop float from stack */
float pop_float(struct node_float **head);

/* Push char onto stack */
void push_char(struct node_char **head, char data);

/* Pop char from stack */
char pop_char(struct node_char **head);

#endif /* STACK_H */
