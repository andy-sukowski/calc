/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Push float onto stack */
void push_float(struct node_float **head, float data)
{
	struct node_float *new = (struct node_float*) malloc(sizeof(struct node_float));
	new->data = data;
	new->next = *head;
	*head = new;
}

/* Pop float from stack */
float pop_float(struct node_float **head)
{
	if (*head == NULL) {
		printf("Error: stack underflow\n");
		exit(EXIT_FAILURE);
	}
	struct node_float *tmp = *head;
	float data = tmp->data;
	*head = tmp->next;
	free(tmp);
	return data;
}

/* Push char onto stack */
void push_char(struct node_char **head, char data)
{
	struct node_char *new = (struct node_char*) malloc(sizeof(struct node_char));
	new->data = data;
	new->next = *head;
	*head = new;
}

/* Pop char from stack */
char pop_char(struct node_char **head)
{
	if (*head == NULL) {
		printf("Error: stack underflow\n");
		exit(EXIT_FAILURE);
	}
	struct node_char *tmp = *head;
	char data = tmp->data;
	*head = tmp->next;
	free(tmp);
	return data;
}
